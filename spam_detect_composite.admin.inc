<?php

/**
 * Settings form callback.
 * @todo Need to group the items together or put them on seperate tabs.
 */
function spam_detect_composite_settings_form() {
	$form = array();

	$form['spam_detect_composite_score_threshold'] = array(
    '#type' => 'textfield',
    '#title' => t('Composite Score Threshold'),
    '#description' => t('Sum of all active filters is divided by this threshold'),
    '#default_value' => variable_get('spam_detect_composite_score_threshold', 15),
    '#max_length' => 2,
    '#size'				=> 2,
  );

	$form['spam_detect_composite_link_body_count'] = array(
    '#type' => 'textfield',
    '#title' => t('Link Count in Body: Threshold'),
    '#description' => t('If link count in text is greater than this number then increase spamminess score.  If lower, decrease spamminess score. Set this to -1 to disable this filter.'),
    '#default_value' => variable_get('spam_detect_composite_link_body_count', 2),
    '#max_length' => 2,
    '#size'				=> 2,
  );

  	$form['spam_detect_composite_link_body_count_decrease_spamminess'] = array(
			'#title' 					=> t('Link Count in Body: Decrease Spamminess Score'),
			'#description' 		=> t('Amount to decrease spamminess if link count < threshold.'),
			'#default_value' 	=> variable_get('spam_detect_composite_link_body_count_decrease_spamminess', 2),
			'#type' 					=> 'textfield',
			'#max_length' 		=> 2,
			'#size'						=> 2,

	);

 	$form['spam_detect_composite_link_body_count_increase_spamminess'] = array(
			'#title' 					=> t('Link Count in Body: Increase Spamminess Score'),
			'#description' 		=> t('Amount to increase spamminess per link if link count > threshold.'),
			'#default_value' 	=> variable_get('spam_detect_composite_link_body_count_increase_spamminess', 1),
			'#type' 					=> 'textfield',
			'#max_length' 		=> 2,
			'#size'						=> 2,

	);

 	$form['spam_detect_composite_body_length_threshold'] = array(
			'#title' 					=> t('Body Length: Threshold'),
			'#description' 		=> t('Minimum character threshold to be consiered a good comment. Set to -1 to disable'),
			'#default_value' 	=> variable_get('spam_detect_composite_body_length_threshold', 20),
			'#type' 					=> 'textfield',
			'#max_length' 		=> 2,
			'#size'						=> 2,

	);

	$form['spam_detect_composite_body_length_increase_spamminess'] = array(
				'#title' 					=> t('Body Length: Increase Spamminess Score'),
				'#description' 		=> t('Amount to increase Spam Score by if Body Length < Threshold'),
				'#default_value' 	=> variable_get('spam_detect_composite_body_length_increase_spamminess', 1),
				'#type' 					=> 'textfield',
				'#max_length' 		=> 2,
				'#size'						=> 2,

		);

	$form['spam_detect_composite_body_length_decrease_spamminess'] = array(
				'#title' 					=> t('Body Length: Decrease Spamminess Score'),
				'#description' 		=> t('Amount to decrease Spam Score by if Body Length > Threshold'),
				'#default_value' 	=> variable_get('spam_detect_composite_body_length_decrease_spamminess', 2),
				'#type' 					=> 'textfield',
				'#max_length' 		=> 2,
				'#size'						=> 2,

		);

	$form['spam_detect_composite_consonants_increase'] = array(
				'#title' 					=> t('Consonants: Increase Spamminess Score'),
				'#description' 		=> t('Amount to increase Spam Score for each occurence of 6 consonants or more in a row.  Set to -1 to disable filter.'),
				'#default_value' 	=> variable_get('spam_detect_composite_consonants_increase', 1),
				'#type' 					=> 'textfield',
				'#max_length' 		=> 2,
				'#size'						=> 2,

		);

		$form['spam_detect_composite_first_word_increase'] = array(
				'#title' 					=> t('First Word is Spammy: Increase Spamminess Score'),
				'#description' 		=> t('Amount to increase Spam Score if first word matches value in list.  Set to -1 to disable filter.'),
				'#default_value' 	=> variable_get('spam_detect_composite_first_word_increase', 10),
				'#type' 					=> 'textfield',
				'#max_length' 		=> 2,
				'#size'						=> 2,

		);
	$form['spam_detect_composite_first_word_list'] = array(
      '#type' => 'textarea',
      '#title' => t('First Word is Spammy List'),
      '#description' => t('Enter each test word on a new line. List is case insensitive and strips out special chars.'),
      '#default_value' => variable_get('spam_detect_composite_first_word_list', _spam_detect_composite_first_word_list()),
    );

	return system_settings_form($form);

}

