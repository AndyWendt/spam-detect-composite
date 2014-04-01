<?php

function _spam_detect_composite_first_word_list() {
  return <<<EOT
Interesting
Sorry
Nice
Cool
EOT;
}

function _spam_detect_composite_tld_list() {
  return <<<EOT
de
pl
cn
EOT;
}

function _spam_detect_composite_word_characters_list() {
  return <<<EOT
.html
.info
?
&
free
EOT;
}

/**
 * Settings form callback.
 *
 * @todo Need to group the items together or put them on separate tabs.
 */
function spam_detect_composite_settings_form() {
  $form = spam_detect_composite_get_settings_form_fields();
  return system_settings_form($form);
}

function spam_detect_composite_get_settings_form_fields() {

  $form = array();

  /////// Composite Score Threshold /////
  $form['spam_detect_composite_score_threshold'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Composite Score Threshold'),
    '#description'   => t('Sum of all active filters is divided by this threshold'),
    '#default_value' => variable_get('spam_detect_composite_score_threshold', 15),
    '#max_length'    => 2,
    '#size'          => 2,
  );

  /////  Links in Body /////
  $form['spam_detect_composite_link_body_count'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Link Count in Body: Threshold'),
    '#description'   => t(
      'If link count in text is greater than this number then increase spamminess score.  If lower, decrease spamminess score. Set this to -1 to disable this filter.'
    ),
    '#default_value' => variable_get('spam_detect_composite_link_body_count', 2),
    '#max_length'    => 2,
    '#size'          => 2,
  );
  $form['spam_detect_composite_link_body_count_decrease_spamminess'] = array(
    '#title'         => t('Link Count in Body: Decrease Spamminess Score'),
    '#description'   => t('Amount to decrease spamminess if link count < threshold.'),
    '#default_value' => variable_get('spam_detect_composite_link_body_count_decrease_spamminess', 2),
    '#type'          => 'textfield',
    '#max_length'    => 2,
    '#size'          => 2,
  );
  $form['spam_detect_composite_link_body_count_increase_spamminess'] = array(
    '#title'         => t('Link Count in Body: Increase Spamminess Score'),
    '#description'   => t('Amount to increase spamminess per link if link count > threshold.'),
    '#default_value' => variable_get('spam_detect_composite_link_body_count_increase_spamminess', 1),
    '#type'          => 'textfield',
    '#max_length'    => 2,
    '#size'          => 2,
  );

  ///// Body Length /////
  $form['spam_detect_composite_body_length_threshold'] = array(
    '#title'         => t('Body Length: Threshold'),
    '#description'   => t('Minimum character threshold to be consiered a good comment. Set to -1 to disable'),
    '#default_value' => variable_get('spam_detect_composite_body_length_threshold', 20),
    '#type'          => 'textfield',
    '#max_length'    => 2,
    '#size'          => 2,
  );

  $form['spam_detect_composite_body_length_increase_spamminess'] = array(
    '#title'         => t('Body Length: Increase Spamminess Score'),
    '#description'   => t('Amount to increase Spam Score by if Body Length < Threshold'),
    '#default_value' => variable_get('spam_detect_composite_body_length_increase_spamminess', 1),
    '#type'          => 'textfield',
    '#max_length'    => 2,
    '#size'          => 2,
  );
  $form['spam_detect_composite_body_length_decrease_spamminess'] = array(
    '#title'         => t('Body Length: Decrease Spamminess Score'),
    '#description'   => t('Amount to decrease Spam Score by if Body Length > Threshold'),
    '#default_value' => variable_get('spam_detect_composite_body_length_decrease_spamminess', 2),
    '#type'          => 'textfield',
    '#max_length'    => 2,
    '#size'          => 2,

  );

  ///// Previous Comments Status ////
  $form['spam_detect_composite_spam_flag_name'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Spam Flag Machine Name'),
    '#description'   => t(
      'Spam Flag machine name created using the Flags Module.  Needed for testing previous comments.'
    ),
    '#default_value' => variable_get('spam_detect_composite_spam_flag_name', 'is_spam'),
    '#max_length'    => 50,
    '#size'          => 50,
  );

  $form['spam_detect_composite_status_of_previous_comments_increase'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Previous Comments from Author: Increase Spamminess Score'),
    '#description'   => t(
      'Amount to increase Spam Score by if previous comment by author is flagged.  Set to -1 to disable.'
    ),
    '#default_value' => variable_get('spam_detect_composite_status_of_previous_comments_increase', 1),
    '#max_length'    => 2,
    '#size'          => 2,
  );
  $form['spam_detect_composite_status_of_previous_comments_decrease'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Previous Comments from Author: Increase Spamminess Score'),
    '#description'   => t(
      'Amount to decrease Spam Score by if previous comment by author is NOT flagged.  Set to -1 to disable.'
    ),
    '#default_value' => variable_get('spam_detect_composite_status_of_previous_comments_decrease', 1),
    '#max_length'    => 2,
    '#size'          => 2,
  );

  ////// Certain Words or Characters //////
  $form['spam_detect_composite_words_characters_increase'] = array(
    '#type'          => 'textfield',
    '#title'         => t('URL Words or Characters: Increase Spamminess Score'),
    '#description'   => t(
      'Amount to increase Spam Score per word or character from list if it is in the URL.  Set to -1 to disable.'
    ),
    '#default_value' => variable_get('spam_detect_composite_words_characters_increase', 1),
    '#max_length'    => 2,
    '#size'          => 2,
  );
  $form['spam_detect_composite_words_characters_list']     = array(
    '#type'          => 'textarea',
    '#title'         => t('URL Words Characters List'),
    '#description'   => t('Enter each value on a new line."'),
    '#default_value' => variable_get(
      'spam_detect_composite_words_characters_list',
      _spam_detect_composite_word_characters_list()
    ),
  );

  ///// TLDs /////
  $form['spam_detect_composite_tld_increase']        = array(
    '#type'          => 'textfield',
    '#title'         => t('TLD: Increase Spamminess Score'),
    '#description'   => t('Amount to increase Spam Score if tld matches value in list.  Set to -1 to disable filter.'),
    '#default_value' => variable_get('spam_detect_composite_tld_increase', 1),
    '#max_length'    => 2,
    '#size'          => 2,
  );
  $form['spam_detect_composite_tld_list']            = array(
    '#type'          => 'textarea',
    '#title'         => t('TLD List'),
    '#description'   => t('Enter each tld on a new line. Supports second level domains such as "co.uk"'),
    '#default_value' => variable_get('spam_detect_composite_tld_list', _spam_detect_composite_tld_list()),
  );

  ///// URL Length //////
  $form['spam_detect_composite_url_length_threshold'] = array(
    '#title'         => t('URL Length: Threshold'),
    '#description'   => t('Threshold for url to be considered spam. Set to -1 to disable.'),
    '#default_value' => variable_get('spam_detect_composite_url_length_threshold', 30),
    '#type'          => 'textfield',
    '#max_length'    => 2,
    '#size'          => 2,
  );
  $form['spam_detect_composite_url_length_increase'] = array(
    '#type'          => 'textfield',
    '#title'         => t('URL Length: Increase Spamminess Score'),
    '#description'   => t('Amount to increase Spam Score if url length > threshold.'),
    '#default_value' => variable_get('spam_detect_composite_url_length_increase', 1),
    '#max_length'    => 2,
    '#size'          => 2,
  );

  ///// Body Starts With /////
  $form['spam_detect_composite_first_word_increase'] = array(
    '#title'         => t('First Word is Spammy: Increase Spamminess Score'),
    '#description'   => t(
      'Amount to increase Spam Score if first word matches value in list.  Set to -1 to disable filter.'
    ),
    '#default_value' => variable_get('spam_detect_composite_first_word_increase', 10),
    '#type'          => 'textfield',
    '#max_length'    => 2,
    '#size'          => 2,
  );
  $form['spam_detect_composite_first_word_list']     = array(
    '#type'          => 'textarea',
    '#title'         => t('First Word is Spammy List'),
    '#description'   => t('Enter each test word on a new line. List is case insensitive and strips out special chars.'),
    '#default_value' => variable_get('spam_detect_composite_first_word_list', _spam_detect_composite_first_word_list()),
  );

  ///// Author Name /////
  $form['spam_detect_composite_author_name_check'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Author Name is Link: Increase Spamminess Score'),
    '#description'   => t(
      'Amount to decrease Spam Score by if author name is a link.  Set to -1 to disable.'
    ),
    '#default_value' => variable_get('spam_detect_composite_status_of_previous_comments_decrease', 2),
    '#max_length'    => 2,
    '#size'          => 2,
  );

  ///// Body Used in Previous Comment /////
  $form['spam_detect_composite_body_in_previous_comment'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Body in Previous Comment: Increase Spamminess Score'),
    '#description'   => t(
      'Amount to increase Spam Score by if the body is the same as the last comment.  Set to -1 to disable.'
    ),
    '#default_value' => variable_get('spam_detect_composite_body_in_previous_comment', 1),
    '#max_length'    => 2,
    '#size'          => 2,
  );

  ///// Random Character Match or Consonants //////
  $form['spam_detect_composite_consonants_increase'] = array(
    '#title'         => t('Consonants: Increase Spamminess Score'),
    '#description'   => t(
      'Amount to increase Spam Score for each occurence of 6 consonants or more in a row.  Set to -1 to disable filter.'
    ),
    '#default_value' => variable_get('spam_detect_composite_consonants_increase', 1),
    '#type'          => 'textfield',
    '#max_length'    => 2,
    '#size'          => 2,
  );

  return $form;
}
