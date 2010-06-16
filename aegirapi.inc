<?php

/**
 * Deferred implementation of hook_autoload_info().
 */
function _aegirapi_autoload_info() {
  return array(
    'AegirPackageApi' => array(
      'file' => 'includes/AegirPackageApi.inc',
    ),
    'AegirPlatformApi' => array(
      'file' => 'includes/AegirPlatformApi.inc',
    ),
    'AegirSiteApi' => array(
      'file' => 'includes/AegirSiteApi.inc',
    ),
    'AegirSiteQueryBuilder' => array(
      'file' => 'includes/AegirSiteQueryBuilder.inc',
    ),
    'AegirTaskApi' => array(
      'file' => 'includes/AegirTaskApi.inc',
    ),
    'AegirTaskQueryBuilder' => array(
      'file' => 'includes/AegirTaskQueryBuilder.inc',
    ),
  );
}

/**
 * Wrapper function around drupal_execute('hosting_task_confirm_form', …).
 *
 * @param object $result
 *  Result object. On failure a error attribute will be set, which may be
 *  complemented with a message and a info attribute. On success the status
 *  attribute is set to 'ok'.
 * @param object $node
 *  The node that the task should be run on.
 * @param string $task
 *  The name of the task.
 * @param array $parameters
 *  The parameters form state values that should be sent to drupal_execute.
 *  Keep in mind that the parameters element in hosting_task_confirm_form has
 *  #tree set to TRUE. Any structures present in the hosting task form of the
 *  task will therefore have to be reflected in the parameters array.
 * @return bool
 *  TRUE on success FALSE on failure. Success in this case doesn't mean that
 *  the task has been successfully run, only that it has passed all validation
 *  functions and has been successfully queued for execution.
 */
function aegirapi_run_hosting_task(object $result, object $node, string $task, array $parameters = array()) {
  $tasks = module_invoke_all('hosting_tasks');

  if (!empty($tasks[$node->type][$task])) {
    $form_state = array();
    $form_state['values'] = array(
      'nid' => $node->nid,
      'task' => $task,
      'parameters' => $parameters,
      'confirm' => 1,
      'op' => $type_tasks[$task]['title'],
      'submit' => $type_tasks[$task]['title'],
    );

    $res = drupal_execute('hosting_task_confirm_form', $form_state, $node, $task);

    if (($errors = form_get_errors())) {
      $result->error = 'failed:406';
      $result->message = sprintf('Failed to %s %s.', $task, $node->type);
      $result->info = $errors;
    }
    else {
      $result->status = 'ok';
    }
  }
  else {
    $result->error = 'task:404';
    $result->message = sprintf('There is no %s task that can be run on nodes of the type %s.', $task, $node->type);
  }

  return empty($result->error);
}
