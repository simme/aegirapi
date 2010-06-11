<?php

class AegirSiteQueryBuilder extends QueryBuilder {
  public function __construct() {
    parent::__construct(TRUE);

    $this->add_table('hs', 'INNER JOIN {hosting_site} AS hs ON hs.vid=n.vid', 'n', array(
      'client' => array(
        'type' => 'int',
        'condition' => QueryBuilder::CONDITION_MATCH,
      ),
      'db_server' => array(
        'type' => 'int',
        'condition' => QueryBuilder::CONDITION_MATCH,
      ),
      'platform' => array(
        'type' => 'int',
        'condition' => QueryBuilder::CONDITION_MATCH,
      ),
      'profile' => array(
        'type' => 'int',
        'condition' => QueryBuilder::CONDITION_MATCH,
      ),
      'site_language' => array(
        'type' => 'string',
        'column' => 'language',
        'condition' => QueryBuilder::CONDITION_MATCH,
      ),
      'last_cron' => array(
        'type' => 'int',
        'condition' => QueryBuilder::CONDITION_MATCH,
      ),
      'site_status' => array(
        'type' => 'int',
        'condition' => QueryBuilder::CONDITION_MATCH,
        'column' => 'status',
      ),
      'verified' => array(
        'type' => 'int',
        'condition' => QueryBuilder::CONDITION_MATCH,
      ),
      'port' => array(
        'type' => 'int',
        'condition' => QueryBuilder::CONDITION_MATCH,
      ),
      'ssl' => array(
        'type' => 'int',
        'condition' => QueryBuilder::CONDITION_MATCH,
      ),
      'ssl_redirect' => array(
        'type' => 'int',
        'condition' => QueryBuilder::CONDITION_MATCH,
      ),
    ));
  }
}