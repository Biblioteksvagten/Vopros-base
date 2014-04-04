<?php
/**
 * @file
 * vopros_base2.default_environment_indicator_environments.inc
 */

/**
 * Implements hook_default_environment_indicator_environment().
 */
function vopros_base_default_environment_indicator_environment() {
  $export = array();

  $environment = new stdClass();
  $environment->disabled = FALSE; /* Edit this to true to make a default environment disabled initially */
  $environment->api_version = 1;
  $environment->machine = 'development';
  $environment->name = 'Development';
  $environment->regexurl = 'dev.biblioteksvagten.dk';
  $environment->settings = array(
    'color' => '#167100',
    'weight' => '',
    'position' => 'top',
    'fixed' => 0,
  );
  $export['development'] = $environment;

  $environment = new stdClass();
  $environment->disabled = FALSE; /* Edit this to true to make a default environment disabled initially */
  $environment->api_version = 1;
  $environment->machine = 'production';
  $environment->name = 'Production';
  $environment->regexurl = 'adm.biblioteksvagten.dk';
  $environment->settings = array(
    'color' => '#e35555',
    'weight' => '',
    'position' => 'top',
    'fixed' => 0,
  );
  $export['production'] = $environment;

  $environment = new stdClass();
  $environment->disabled = FALSE; /* Edit this to true to make a default environment disabled initially */
  $environment->api_version = 1;
  $environment->machine = 'vopros';
  $environment->name = 'Vopros';
  $environment->regexurl = 'vopros.biblioteksvagten.dk';
  $environment->settings = array(
    'color' => '#9a6b00',
    'weight' => '',
    'position' => 'top',
    'fixed' => 0,
  );
  $export['vopros'] = $environment;

  $environment = new stdClass();
  $environment->disabled = FALSE; /* Edit this to true to make a default environment disabled initially */
  $environment->api_version = 1;
  $environment->machine = 'forsk';
  $environment->name = 'Forsk';
  $environment->regexurl = 'forsk.biblioteksvagten.dk';
  $environment->settings = array(
    'color' => '#004371',
    'weight' => '',
    'position' => 'top',
    'fixed' => 0,
  );
  $export['forsk'] = $environment;

  return $export;
}