<?php
/**
 * @file
 * spam_detect_composite_example.features.inc
 */

/**
 * Implements hook_flag_default_flags().
 */
function spam_detect_composite_example_flag_default_flags() {
  $flags = array();
  // Exported flag: "Spam Flamethrower".
  $flags['is_spam'] = array(
    'entity_type' => 'comment',
    'title' => 'Is Spam',
    'global' => 1,
    'types' => array(),
    'flag_short' => 'Mark as Spam',
    'flag_long' => 'Mark as Spam',
    'flag_message' => 'Goodbye Spam!',
    'unflag_short' => 'Unflag as Spam',
    'unflag_long' => 'Mark as NOT Spam',
    'unflag_message' => 'Marked as NOT Spam',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 1,
    'api_version' => 3,
    'module' => 'spam_detect_composite_example',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}
