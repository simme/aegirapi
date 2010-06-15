<?php

/**
 * Package API definition and implementation.
 */
class AegirPackageApi {

  /**
   * Retrieves package information
   *
   * @param int $nid ["path", "0"]
   *  The nid of the platform.
   * @return object
   *
   * @Access(callback='user_access', args={'aegirapi retrieve package info'})
   */
  public static function retrieve($nid) {
    $node = node_load($nid);

    // Check that it indeed was a package that the user tried to access.
    if ($node && $node->type !== 'package') {
      $node = NULL;
    }

    return $node;
  }
}