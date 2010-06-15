<?php

/**
 * Platform API definition and implementation.
 *
 * @Relationship(name='packages', controller='listPackages')
 */
class AegirPlatformApi {

  /**
   * Retrieves a listing of platforms.
   *
   * @return array
   *
   * @Access(callback='user_access', args={'aegirapi use api'})
   */
  public static function index() {
    return _hosting_get_platforms();
  }

  /**
   * Retrieves platform information
   *
   * @param int $nid ["path", "0"]
   *  The nid of the platform.
   * @param bool $with_profiles ["param", "with_profiles"]
   *  Whether to get the profiles for the platform.
   * @return object
   *
   * @Access(callback='user_access', args={'aegirapi retrieve platform info'})
   */
  public static function retrieve($nid, $with_profiles = FALSE) {
    $node = node_load($nid);

    // Check that it indeed was a platform that the user tried to access.
    if ($node && $node->type !== 'platform') {
      $node = NULL;
    }

    // Load profiles if they were requested.
    if ($with_profiles && $node) {
      $node->available_profiles = hosting_get_profiles($nid);
    }

    return $node;
  }

  /**
   * Lists packages for the platform.
   *
   * @param int $nid ["path", "0"]
   *  The nid of the platform.
   * @param string $type ["param", "type"]
   *  The type of packages to list.
   * @return array
   *
   * @Access(callback='user_access', args={'aegirapi retrieve platform info'})
   */
  public static function listPackages($nid, $type = NULL) {
    $packages = array();

    $args = array(
      'rid' => $platform,
      'n.status' => 1,
    );

    if ($type) {
      $args['package_type'] = 'profile';
    }

    return hosting_package_instances_load($args);
  }
}