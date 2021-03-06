<?php

/**
 * @ file
 * Public page callback functions.
 */

/**
 * Page callback to create questions.
 *
 * Used by Open Question to create questions
 */
function vopros_question_create_service() {
  $question = vopros_question_new();
  $question_wrapper = entity_metadata_wrapper('vopros_question', $question);
  $post_data = array();
  // Reformat all the post data to not use CamelCase.
  foreach ($_POST as $key => $value) {
    $post_data[strtolower(preg_replace('/(?<=\\w)(?=[A-Z])/',"_$1", $key))] = $value;
  }
  $properties = $question_wrapper->getPropertyInfo();
  // Populate the question with the needed info
  foreach ($properties as $property => $info) {
    if (isset($post_data[$property])) {
      $question->{$property} = $post_data[$property];
    }
  }
  if (!empty($_POST['questionAttachmentData'])) {
    $file = file_save_data(base64_decode($_POST['questionAttachmentData']));
    if ($file) {
      $file_data = array(
        'fid' => $file->fid,
        'display' => 1,
        'description' => '',
      );
      $question_wrapper->vopros_question_attachment[0] = $file_data;
    }
  }
  if (module_exists('vopros_editorial') && !empty($_POST['vopros_editorial'])) {
    unset($question->vopros_editorial);
    $vocab = taxonomy_vocabulary_machine_name_load('vopros_editorial');
    $terms = taxonomy_term_load_multiple(FALSE, array('name' => $_POST['vopros_editorial'], 'vid' => $vocab->vid));
    if ($terms) {
      $term = array_shift($terms);
      $question_wrapper->vopros_editorial = $term;
    }
  }
  if (!empty($post_data)) {
  $validation = vopros_question_validate_data($question);
    if ($validation['status'] == 'valid') {
      $question_wrapper->save();
      print 'Question created';
      exit();
    }
    drupal_add_http_header('Status', '400');
    $errors = array();
    foreach ($validation['errors'] as $value) {
      $errors[] = $value[0];
    }
    watchdog('vopros_question', 'Could not create vopros question, invalid data for: %fields. Validation object: %validation, POST data: %post', array('%fields' => implode(', ', $errors), '%validation' => print_r($validation, TRUE), '%post' => print_r($_POST, TRUE)), WATCHDOG_ERROR);
  }
  print 'Question not created';
  exit();
}


/**
 * Page callback to create questions.
 *
 * Used by SMS service to create questions
 */
function vopros_question_create_sms() {
  $default_values = array(
    'user_answer_preference' => 'sms',
    'agency_id' => 'SMS1919',
  );

  $question = vopros_question_new($default_values);
  $message = isset($_GET['msg']) ? iconv('CP1252', 'UTF-8', $_GET['msg']) : '';
  $phone = isset($_GET['origin']) ? $_GET['origin'] : '';
  if ($message && $phone) {
    $words = explode(' ', $message);
    $keyword = array_shift($words);
    $question->qanda_service_name = 'sms';
    $question->question_content = implode(' ', $words);
    $question->user_mobile_phone = $phone;
    $question->question_deadline = 2;
    if (module_exists('vopros_editorial') && $tid = variable_get('vopros_question_default_sms_editoral', '')) {
      $question_wrapper = entity_metadata_wrapper('vopros_question', $question);
      $question_wrapper->vopros_editorial = $tid;
    }
    if (!trim($question->question_content)) {
      $question->question_content = t('Empty question - no content delivered from SMS service.');
    }
    $question->save();
  }
  $output =
'<?xml version="1.0" encoding="iso-8859-1"?>
  <action>
    <type>terminate</type>
  </action>';
  print $output;
  exit();
}
