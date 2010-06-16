<?php

/**
 * Task API definition and implementation.
 *
 */
class AegirTaskApi {

  /**
   * Retrieves a listing of tasks.
   *
   * @param int $page ["param","page"]
   * @param string $fields ["param","fields"]
   * @param array $parameters ["param"]
   * @return array
   *
   * @Access(callback='user_access', args={'aegirapi retrieve task info'})
   */
  public static function index($page=0, $fields=array(), $parameters=array()) {
    $builder = new AegirTaskQueryBuilder();

    if ($parameters['__action'] == 'describe') {
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

    // Always enforce the node status condition and type
    $parameters['status'] = 1;
    $parameters['type'] = 'task';

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
   * Retrieves task information
   *
   * @param int $nid ["path", "0"]
   *  The nid of the task.
   * @return object
   *
   * @Access(callback='user_access', args={'aegirapi retrieve task info'})
   */
  public static function retrieve($nid) {
    $node = node_load($nid);

    // Check that it indeed was a task that the user tried to access.
    if ($node && $node->type !== 'task') {
      $node = NULL;
    }

    return $node;
  }
}
