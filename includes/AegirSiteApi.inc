<?php

/**
 * Site API definition and implementation.
 *
 * @TargetedAction(name='migrate', controller='migrateTo')
 * @TargetedAction(name='backup', controller='backup')
 */
class AegirSiteApi {

  /**
   * Retrieves a listing of sites.
   *
   * @param int $page ["param","page"]
   * @param string $fields ["param","fields"]
   * @param array $parameters ["param"]
   * @return array
   *
   * @Access(callback='user_access', args={'aegirapi retrieve site info'})
   */
  public static function index($page=0, $fields=array(), $parameters=array()) {
    $builder = new AegirSiteQueryBuilder();

    if ($parameters['__action']=='describe') {
      return $builder->describe();
    }

    if (empty($fields)) {
      $fields = array('nid', 'title');
    }
    else {
      if (is_string($fields)) {
        $fields = preg_split('/,\s?/', $fields);
      }
      $fields = array_fill_keys($fields, TRUE);
      $fields['nid'] = TRUE;
      $fields = array_keys($fields);
    }

    // Always enforce the node status condition
    $parameters['status'] = 1;
    $parameters['type'] = 'site';

    // Generate and execute the sql
    list($sql, $params) = $builder->query($fields, $parameters);
    $res = db_query_range($sql, $params, $page*20, 20);

    $nodes = array();
    while ($node = db_fetch_object($res)) {
      $nodes[] = $node;
    }

    return $nodes;
  }

  /**
   * Retrieves site information
   *
   * @param int $nid ["path", "0"]
   *  The nid of the site.
   * @return object
   *
   * @Access(callback='user_access', args={'aegirapi retrieve site info'})
   */
  public static function retrieve($nid) {
    $node = node_load($nid);

    // Check that it indeed was a site that the user tried to access.
    if ($node && $node->type !== 'site') {
      $node = NULL;
    }

    return $node;
  }

  /**
   * Creates a site.
   *
   * @param object $data ["data"]
   * @return object
   *
   * @Access(callback='user_access', args={'aegirapi create site'})
   */
  public static function create($data) {
    global $user;

    $result = (object)array();

    $node = array(
      'type' => 'site',
      'title' => $data->domain,
      'platform' => $data->platform,
      'profile' => $data->profile,
      'client' => $data->client,
      'uid' => $user->uid,
    );
    drupal_alter('aegirapi_create_site', $node, $data);

    // Load the required includes for drupal_execute
    module_load_include('inc', 'node', 'node.pages');
    $nid = NULL;

    // Setup form_state
    $form_state = array();
    $form_state['values'] = $node;
    $form_state['values']['op'] = t('Save');
    $ret = drupal_execute('site_node_form', $form_state, $node);

    if (($errors = form_get_errors())) {
      $result->error = 'failed:406';
      $result->message = 'Failed to create site';
      $result->info = $errors;
    }
    else {
      // Fetch $nid out of $form_state
      $nid = $form_state['nid'];

      // Load the newly created node.
      $node = node_load($nid);
      module_invoke_all('aegirapi_site_created', $node, $data);

      $result->nid = $nid;
      $result->status = 'ok';
    }

    return $result;
  }

  /**
   * Migrates a site to another platform.
   *
   * @param int $nid ["path", 0]
   * @param int $platform ["param", "platform"]
   * @return object
   *
   * @Access(callback='user_access', args={'aegirapi migrate site'})
   */
  public static function migrateTo($nid, $platform) {
    $result = (object)array();

    $node = node_load($nid);
    $platform_node = node_load($platform);

    if (!$node || $node->type !== 'site') {
      $result->error = 'site:404';
      $result->message = "Site not found";
    }
    else if (!$platform_node || $platform_node->type !== 'platform') {
      $result->error = 'platform:404';
      $result->message = "Platform not found";
    }
    else {
      module_load_include('inc', 'aegirapi');
      aegirapi_run_hosting_task($result, $node, 'migrate', array(
        'target_platform' => $platform,
      ));
    }

    return $result;
  }

  /**
   * Backup a site.
   *
   * @param int $nid ["path", 0]
   * @return object
   *
   * @Access(callback='user_access', args={'aegirapi backup site'})
   */
  public static function backup($nid) {
    $result = (object)array();

    $node = node_load($nid);
    $platform_node = node_load($platform);

    if (!$node || $node->type !== 'site') {
      $result->error = 'site:404';
      $result->message = "Site not found";
    }
    else {
      module_load_include('inc', 'aegirapi');
      aegirapi_run_hosting_task($result, $node, 'backup');
    }

    return $result;
  }
}
