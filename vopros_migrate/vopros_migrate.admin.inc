<?php

/**
 * General settings form.
 */
function vopros_migrate_setting_form($form, &$form_state) {
  $connect = vopros_migrate_connect();
  if (!$connect) {
    drupal_set_message(t('Could not connect to the Vopros migration database'), 'error');
  }
  else {
    drupal_set_message(t('Successfully connected to Vopros migration database'));
  }

  $form['database_configuration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Database configuration'),
    '#description' => t('Setup the connection to the external database you want to use as source for the migration of data.'),
    '#collapsible' => TRUE,
    '#collapsed' => $connect,
    '#access' => user_access('administer vopros_migrate'),
  );

  $form['database_configuration']['vopros_migrate_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Host'),
    '#description' => t('The IP address to the database.'),
    '#default_value' => variable_get('vopros_migrate_host', ''),
  );

  $form['database_configuration']['vopros_migrate_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('The Username used to login to the database.'),
    '#default_value' => variable_get('vopros_migrate_username', ''),
  );

  $form['database_configuration']['vopros_migrate_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#description' => t('The password for the database.'),
    '#default_value' => variable_get('vopros_migrate_password', ''),
  );

  $form['database_configuration']['vopros_migrate_database'] = array(
    '#type' => 'textfield',
    '#title' => t('Database name'),
    '#description' => t('The name of the database.'),
    '#default_value' => variable_get('vopros_migrate_database', ''),
  );

  $form['database_configuration']['vopros_migrate_driver'] = array(
    '#type' => 'select',
    '#title' => t('Database driver'),
    '#options' => array(
      'mssql' => t('Mssql'),
    ),
  );

  return system_settings_form($form);
}

/**
 * Form to perform migration of questions
 */
function vopros_migrate_perform_migrate_questions($form, &$form_state) {
  $form['count'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of questions to migrate'),
  );

  $form['migrate'] = array(
    '#type' => 'submit',
    '#value' => t('Migrate'),
  );

  return $form;
}

/**
 * Validate handler for vopros_migrate_perform_migrate_questions().
 */
function vopros_migrate_perform_migrate_questions_validate(&$form, &$form_state) {
  if (!is_numeric($form_state['values']['count'])) {
    form_set_error('count', t('Must be a number'));
  }
}

/**
 * Submit handler for vopros_migrate_perform_migrate_questions().
 */
function vopros_migrate_perform_migrate_questions_submit(&$form, &$form_state) {
  $count = $form_state['values']['count'];
  $batch = array(
    'title' => t('Importing users from external database'),
    'operations' => array(
      array('_vopros_migrate_perform_migrate_questions', array($count)),
    ),
    'finished' => 'vopros_migrate_questions_batch_finished',
    'file' => drupal_get_path('module', 'vopros_migrate') . '/vopros_migrate.admin.inc',
  );
  batch_set($batch);
}

/**
 * Callback for when user import batch job is finished.
 */
function vopros_migrate_questions_batch_finished($success, $results, $operations) {
  // The 'success' parameter means no fatal PHP errors were detected. All
  // other error management should be handled using 'results'.
  if ($success) {
    $message = format_plural($results['count'], 'One question and answer imported.', '@count questions and answers imported.');
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
}

/**
 * Form to perform migration of users
 */
function vopros_migrate_perform_migrate_users($form, &$form_state) {
  $form['count'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of users to migrate'),
  );

  $form['migrate'] = array(
    '#type' => 'submit',
    '#value' => t('Migrate'),
  );

  return $form;
}

/**
 * Validate handler for vopros_migrate_perform_migrate_questions().
 */
function vopros_migrate_perform_migrate_users_validate(&$form, &$form_state) {
  if (!is_numeric($form_state['values']['count'])) {
    form_set_error('count', t('Must be a number'));
  }
}

/**
 * Submit handler for vopros_migrate_perform_migrate_questions().
 */
function vopros_migrate_perform_migrate_users_submit(&$form, &$form_state) {
  $count = $form_state['values']['count'];
  $batch = array(
    'title' => t('Importing users from external database'),
    'operations' => array(
      array('_vopros_migrate_perform_migrate_users', array($count)),
    ),
    'finished' => 'vopros_migrate_users_batch_finished',
    'file' => drupal_get_path('module', 'vopros_migrate') . '/vopros_migrate.admin.inc',
  );
  batch_set($batch);
}

/**
 * Callback for when user import batch job is finished.
 */
function vopros_migrate_users_batch_finished($success, $results, $operations) {
  // The 'success' parameter means no fatal PHP errors were detected. All
  // other error management should be handled using 'results'.
  if ($success) {
    $message = format_plural($results['count'], 'One user imported.', '@count users imported.');
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
}

/**
 * Form to perform migration of taxonomy terms
 */
function vopros_migrate_perform_migrate_vocabolary($form, &$form_state) {
  $form['count'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of terms to migrate'),
  );

  $form['migrate'] = array(
    '#type' => 'submit',
    '#value' => t('Migrate'),
  );

  return $form;
}

/**
 * Validate handler for vopros_migrate_perform_migrate_questions().
 */
function vopros_migrate_perform_migrate_vocabolary_validate(&$form, &$form_state) {
  if (!is_numeric($form_state['values']['count'])) {
    form_set_error('count', t('Must be a number'));
  }
}

/**
 * Submit handler for vopros_migrate_perform_migrate_questions().
 */
function vopros_migrate_perform_migrate_vocabolary_submit(&$form, &$form_state) {
  $count = $form_state['values']['count'];
  $batch = array(
    'title' => t('Importing taxonomy terms from external database'),
    'operations' => array(
      array('_vopros_migrate_perform_migrate_vocabolary', array($count)),
    ),
    'finished' => 'vopros_migrate_terms_batch_finished',
    'file' => drupal_get_path('module', 'vopros_migrate') . '/vopros_migrate.admin.inc',
  );
  batch_set($batch);
}

/**
 * Callback for when term import batch job is finished.
 */
function vopros_migrate_terms_batch_finished($success, $results, $operations) {
  // The 'success' parameter means no fatal PHP errors were detected. All
  // other error management should be handled using 'results'.
  if ($success) {
    $message = format_plural($results['count'], 'One term imported.', '@count terms imported.');
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
}

/**
 * Form to perform migration of public questions.
 */
function vopros_migrate_perform_migrate_public_questions($form, &$form_state) {
  $form['count'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of public questions to migrate'),
  );

  $form['migrate'] = array(
    '#type' => 'submit',
    '#value' => t('Migrate'),
  );

  return $form;
}

/**
 * Validate handler for vopros_migrate_perform_migrate_questions().
 */
function vopros_migrate_perform_migrate_public_questions_validate(&$form, &$form_state) {
  if (!is_numeric($form_state['values']['count'])) {
    form_set_error('count', t('Must be a number'));
  }
}

/**
 * Submit handler for vopros_migrate_perform_migrate_questions().
 */
function vopros_migrate_perform_migrate_public_questions_submit(&$form, &$form_state) {
  $count = $form_state['values']['count'];
  $batch = array(
    'title' => t('Importing public questions from external database'),
    'operations' => array(
      array('_vopros_migrate_perform_migrate_public_questions', array($count)),
    ),
    'finished' => 'vopros_migrate_public_questions_batch_finished',
    'file' => drupal_get_path('module', 'vopros_migrate') . '/vopros_migrate.admin.inc',
  );
  batch_set($batch);
}

/**
 * Callback for when public question import batch job is finished.
 */
function vopros_migrate_public_questions_batch_finished($success, $results, $operations) {
  // The 'success' parameter means no fatal PHP errors were detected. All
  // other error management should be handled using 'results'.
  if ($success) {
    $message = format_plural($results['count'], 'One public question imported.', '@count public questions imported.');
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
}

/**
 * Form to clenaup migration of public questions.
 */
function vopros_migrate_clean_up_migrate_public_questions($form, &$form_state) {
  $form['count'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of public questions to clean up'),
  );

  $form['migrate'] = array(
    '#type' => 'submit',
    '#value' => t('Migrate'),
  );

  return $form;
}

/**
 * Validate handler for vopros_migrate_perform_migrate_questions().
 */
function vopros_migrate_clean_up_migrate_public_questions_validate(&$form, &$form_state) {
  if (!is_numeric($form_state['values']['count'])) {
    form_set_error('count', t('Must be a number'));
  }
}

/**
 * Submit handler for vopros_migrate_perform_migrate_questions().
 */
function vopros_migrate_clean_up_migrate_public_questions_submit(&$form, &$form_state) {
  $count = $form_state['values']['count'];
  $batch = array(
    'title' => t('Cleaning up public questions migrated from external database'),
    'operations' => array(
      array('_vopros_migrate_clean_up_migrate_public_questions', array($count)),
    ),
    'finished' => 'vopros_migrate_clean_up_public_questions_batch_finished',
    'file' => drupal_get_path('module', 'vopros_migrate') . '/vopros_migrate.admin.inc',
  );
  batch_set($batch);
}

/**
 * Callback for when public question import batch job is finished.
 */
function vopros_migrate_clean_up_public_questions_batch_finished($success, $results, $operations) {
  // The 'success' parameter means no fatal PHP errors were detected. All
  // other error management should be handled using 'results'.
  if ($success) {
    $message = format_plural($results['count'], 'One public question cleaned up.', '@count public questions cleaned up.');
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
}
