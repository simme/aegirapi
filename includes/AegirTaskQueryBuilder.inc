<?php

class AegirTaskQueryBuilder extends QueryBuilder {
  public function __construct() {
    parent::__construct(TRUE);

    $this->add_table('ht', 'INNER JOIN {hosting_task} AS ht ON ht.vid=n.vid', 'n', array(
      'task_type' => array(
        'type' => 'string',
        'condition' => QueryBuilder::CONDITION_MATCH,
      ),
      'site' => array(
        'type' => 'int',
        'condition' => QueryBuilder::CONDITION_MATCH,
        'column' => 'rid',
      ),
      'task_status' => array(
        'type' => 'int',
        'condition' => QueryBuilder::CONDITION_MATCH,
      ),
      'executed' => array(
        'type' => 'int',
        'condition' => QueryBuilder::CONDITION_RANGE,
      ),
      'delta' => array(
        'type' => 'int',
        'condition' => QueryBuilder::CONDITION_MATCH,
      ),
    ));
  }
}