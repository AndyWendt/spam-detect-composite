<?php
/**
 * Validate function for our settings form.
 */
function spam_detect_composite_settings_form_validate($form, $form_state) {

  /////// Composite Score Threshold /////
  if (
    !is_numeric($form_state['values']['spam_detect_composite_score_threshold'])
    OR $form_state['values']['spam_detect_composite_score_threshold'] <= 0
    OR $form_state['values']['spam_detect_composite_score_threshold'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_score_threshold',
      t('Composite Score Threshold value must be between 1 and 99')
    );
  }

  /////  Links in Body /////
  if (
    !is_numeric($form_state['values']['spam_detect_composite_link_body_count'])
    OR $form_state['values']['spam_detect_composite_link_body_count'] < -1
    OR $form_state['values']['spam_detect_composite_link_body_count'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_link_body_count',
      t('Link Count in Body: Threshold value must be between -1 and 99')
    );
  }

  if (
    !is_numeric($form_state['values']['spam_detect_composite_link_body_count_decrease_spamminess'])
    OR $form_state['values']['spam_detect_composite_link_body_count_decrease_spamminess'] < 0
    OR $form_state['values']['spam_detect_composite_link_body_count_decrease_spamminess'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_link_body_count_decrease_spamminess',
      t('Link Count in Body: Decrease Value must be between 0 and 99')
    );
  }

  if (
    !is_numeric($form_state['values']['spam_detect_composite_link_body_count_increase_spamminess'])
    OR $form_state['values']['spam_detect_composite_link_body_count_increase_spamminess'] < 0
    OR $form_state['values']['spam_detect_composite_link_body_count_increase_spamminess'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_link_body_count_increase_spamminess',
      t('Link Count in Body: Increase value must be between 0 and 99')
    );
  }


  ///// Body Length /////
  if (
    !is_numeric($form_state['values']['spam_detect_composite_body_length_threshold'])
    OR $form_state['values']['spam_detect_composite_body_length_threshold'] < -1
    OR $form_state['values']['spam_detect_composite_body_length_threshold'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_body_length_threshold',
      t('Body Length: Threshold value must be between -1 and 99')
    );
  }

  if (
    !is_numeric($form_state['values']['spam_detect_composite_body_length_increase_spamminess'])
    OR $form_state['values']['spam_detect_composite_body_length_increase_spamminess'] < 0
    OR $form_state['values']['spam_detect_composite_body_length_increase_spamminess'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_body_length_increase_spamminess',
      t('Body Length: Increase value must be between 0 and 99')
    );
  }

  if (
    !is_numeric($form_state['values']['spam_detect_composite_body_length_decrease_spamminess'])
    OR $form_state['values']['spam_detect_composite_body_length_decrease_spamminess'] < 0
    OR $form_state['values']['spam_detect_composite_body_length_decrease_spamminess'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_body_length_decrease_spamminess',
      t('Body Length: Decrease value must be between 0 and 99')
    );
  }

  ///// Previous Comments Status ////
  if (
    //todo change to preg_match
    !is_string($form_state['values']['spam_detect_composite_spam_flag_name'])
  ) {
    form_set_error('spam_detect_composite_spam_flag_name', t('Spam flag machine name must be a string'));
  }

  if (
    !is_numeric($form_state['values']['spam_detect_composite_status_of_previous_comments_increase'])
    OR $form_state['values']['spam_detect_composite_status_of_previous_comments_increase'] < -1
    OR $form_state['values']['spam_detect_composite_status_of_previous_comments_increase'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_status_of_previous_comments_increase',
      t('Previous Comments from Author: Increase value must be between -1 and 99')
    );
  }

  if (
    !is_numeric($form_state['values']['spam_detect_composite_status_of_previous_comments_decrease'])
    OR $form_state['values']['spam_detect_composite_status_of_previous_comments_decrease'] < 0
    OR $form_state['values']['spam_detect_composite_status_of_previous_comments_decrease'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_status_of_previous_comments_decrease',
      t('Previous Comments from Author: Decrease value must be between 0 and 99')
    );
  }

  ////// Certain Words or Characters //////
  if (
    !is_numeric($form_state['values']['spam_detect_composite_words_characters_increase'])
    OR $form_state['values']['spam_detect_composite_words_characters_increase'] < -1
    OR $form_state['values']['spam_detect_composite_words_characters_increase'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_words_characters_increase',
      t('Url Words or Characters: Increase value must be between -1 and 99')
    );
  }

  if (
    //todo change to preg_match
  !is_string($form_state['values']['spam_detect_composite_words_characters_list'])
  ) {
    form_set_error('spam_detect_composite_words_characters_list', t('Url Words Character List must be a string'));
  }

  ///// TLDs /////
  if (
    !is_numeric($form_state['values']['spam_detect_composite_tld_increase'])
    OR $form_state['values']['spam_detect_composite_tld_increase'] < -1
    OR $form_state['values']['spam_detect_composite_tld_increase'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_tld_increase',
      t('TLD: Increase value must be between -1 and 99')
    );
  }

  if (
    //todo change to preg_match
  !is_string($form_state['values']['spam_detect_composite_tld_list'])
  ) {
    form_set_error('spam_detect_composite_tld_list', t('TLD List must be a string'));
  }

  ///// URL Length //////
  if (
    !is_numeric($form_state['values']['spam_detect_composite_url_length_threshold'])
    OR $form_state['values']['spam_detect_composite_url_length_threshold'] < -1
    OR $form_state['values']['spam_detect_composite_url_length_threshold'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_url_length_threshold',
      t('URL Length: Increase value must be between -1 and 99')
    );
  }

  if (
    !is_numeric($form_state['values']['spam_detect_composite_url_length_increase'])
    OR $form_state['values']['spam_detect_composite_url_length_increase'] < 0
    OR $form_state['values']['spam_detect_composite_url_length_increase'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_url_length_increase',
      t('URL Length: Increase value must be between 0 and 99')
    );
  }


  ///// Body Starts With /////
  if (
    !is_numeric($form_state['values']['spam_detect_composite_first_word_increase'])
    OR $form_state['values']['spam_detect_composite_first_word_increase'] < -1
    OR $form_state['values']['spam_detect_composite_first_word_increase'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_first_word_increase',
      t('First Word is Spammy: Increase value must be between -1 and 99')
    );
  }

  if (
    //todo change to preg_match
  !is_string($form_state['values']['spam_detect_composite_first_word_list'])
  ) {
    form_set_error('spam_detect_composite_first_word_list', t('First Word List must be a string'));
  }

  ///// Author Name /////
  if (
    !is_numeric($form_state['values']['spam_detect_composite_author_name_check'])
    OR $form_state['values']['spam_detect_composite_author_name_check'] < -1
    OR $form_state['values']['spam_detect_composite_author_name_check'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_author_name_check',
      t('Author Name is Link: Increase value must be between -1 and 99')
    );
  }

  ///// Body Used in Previous Comment /////
  if (
    !is_numeric($form_state['values']['spam_detect_composite_body_in_previous_comment'])
    OR $form_state['values']['spam_detect_composite_body_in_previous_comment'] < -1
    OR $form_state['values']['spam_detect_composite_body_in_previous_comment'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_body_in_previous_comment',
      t('Body in Previous Comment: Increase value must be between -1 and 99')
    );
  }

  ///// Random Character Match or Consonants //////
  if (
    !is_numeric($form_state['values']['spam_detect_composite_consonants_increase'])
    OR $form_state['values']['spam_detect_composite_consonants_increase'] < -1
    OR $form_state['values']['spam_detect_composite_consonants_increase'] > 99
  ) {
    form_set_error(
      'spam_detect_composite_consonants_increase',
      t('Consonants: Increase value must be between -1 and 99')
    );
  }
}
