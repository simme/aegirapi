<?php

/**
 * Implementation of hook_default_oauth_common_context().
 */
function agirapi_features_default_oauth_common_context() {
  module_load_include('inc', 'agirapi_features', 'agirapi_features.defaults');
  $args = func_get_args();
  return call_user_func_array('_agirapi_features_default_oauth_common_context', $args);
}

/**
 * Implementation of hook_default_services_endpoint().
 */
function agirapi_features_default_services_endpoint() {
  module_load_include('inc', 'agirapi_features', 'agirapi_features.defaults');
  $args = func_get_args();
  return call_user_func_array('_agirapi_features_default_services_endpoint', $args);
}
