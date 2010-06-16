<?php

/**
 * Helper to implementation of hook_default_oauth_common_context().
 */
function _agirapi_features_default_oauth_common_context() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->name = 'aegirapi';
  $context->title = 'Ægir API';
  $context->authorization_options = array(
    'access_token_lifetime' => 0,
    'message' => 'This will allow @appname to access the Ægir API',
    'disable_auth_level_selection' => 1,
    'signature_methods' => array(
      '0' => 'HMAC-SHA1',
      '1' => 'HMAC-SHA256',
      '2' => 'HMAC-SHA384',
      '3' => 'HMAC-SHA512',
    ),
    'default_authorization_levels' => array(
      '0' => '*',
    ),
  );
  $context->authorization_levels = array(
    '*' => array(
      'name' => '*',
      'title' => 'API Access',
      'description' => 'Allows @appname access the Ægir API',
      'default' => 1,
      'delete' => 0,
    ),
  );

  $export['aegirapi'] = $context;
  return $export;
}

/**
 * Helper to implementation of hook_default_services_endpoint().
 */
function _agirapi_features_default_services_endpoint() {
  $export = array();
  $endpoint = new stdClass;
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->name = 'aegirapi';
  $endpoint->title = 'Ægir API';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'aegir/api';
  $endpoint->authentication = array(
    'services_oauth' => array(
      'oauth_context' => 'aegirapi',
    ),
  );
  $endpoint->resources = array(
    'aegir-platform' => array(
      'alias' => 'platform',
      'operations' => array(
        'retrieve' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
        'index' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
      ),
      'relationships' => array(
        'packages' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
      ),
    ),
    'aegir-package' => array(
      'alias' => 'package',
      'operations' => array(
        'retrieve' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
      ),
    ),
    'aegir-site' => array(
      'alias' => 'site',
      'operations' => array(
        'create' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
        'retrieve' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
        'index' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
      ),
      'actions' => array(
        'migrate' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
        'backup' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
      ),
      'targeted actions' => array(
        'migrate' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
        'backup' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
      ),
    ),
    'aegir-task' => array(
      'alias' => 'task',
      'operations' => array(
        'retrieve' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
        'index' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
      ),
      'relationships' => array(
        'revisions' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
        'log' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
      ),
    ),
  );

  $export['aegirapi'] = $endpoint;
  return $export;
}
