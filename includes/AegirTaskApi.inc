<?php

/**
 * Task API definition and implementation.
 *
 * @Relationship(name='revisions', controller='revisions')
 * @Relationship(name='log', controller='log')
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

  /**
   * Retrieves task revisions
   *
   * @param int $nid ["path", "0"]
   *  The nid of the task.
   * @return array
   *
   * @Access(callback='user_access', args={'aegirapi retrieve task info'})
   */
  public static function revisions($nid) {
    $revisions = array();
    $res = db_query("SELECT * FROM {hosting_task}
      WHERE nid = %d
      ORDER BY executed ASC", array(
        ':nid' => $nid,
    ));

    while (($revision = db_fetch_object($res))) {
      $revisions[] = $revision;
    }

    return $revisions;
  }

  /**
   * Retrieves the log for a task revision
   *
   * @param int $nid ["path", "0"]
   *  The nid of the task.
   * @param int $vid ["param", "revision"]
   *  Optional. The vid of the task revision. If omitted you will get the log
   *  of the latest revision.
   * @return array
   *
   * @Access(callback='user_access', args={'aegirapi retrieve task info'})
   */
  public static function taskLog($nid, $vid = NULL) {
    $log = array();

    if ($vid === NULL) {
      $vid = db_result(db_query("SELECT vid FROM {node} WHERE nid=%d", $nid));
    }

    $res = db_query("SELECT * FROM {hosting_task_log}
      WHERE vid = %d
      ORDER BY `timestamp` ASC, lid ASC", array(
        ':vid' => $vid,
    ));

    while (($item = db_fetch_object($res))) {
      $log[] = $item;
    }

    return $log;
  }
}
