<?php

function spam_detect_composite_find_links($text) {
  // Regex by John Gruber: http://daringfireball.net/2010/07/improved_regex_for_matching_urls // License: Public Domain
  $regex = '~(?i)\b((?:https?://|www\d{0,3}[.]|[a-z0-9.\-]+[.][a-z]{2,4}/)(?:[^\s()<>]+|\(([^\s()<>]+|(\([^\s()<>]+\)))
  *\))+(?:\(([^\s()<>]+|(\([^\s()<>]+\)))*\)|[^\s`!()\[\]{};:\'".,<>?«»“”‘’]))~';
  preg_match_all($regex, $text, $links_array);
  return $links_array[0];
}

function spam_detect_get_all_comments_with_flags() {
  $query = 'SELECT c.cid, c.nid, c.subject, c.name, c.mail as email, c.homepage as author_url, d.comment_body_value as body, fl.name as
            flag_name, fc.fid as flag_id, fc.count as flag_count
             FROM {comment} c
             LEFT JOIN {field_data_comment_body} d ON c.cid = d.entity_id
             LEFT JOIN {flag_counts} fc ON c.cid = fc.entity_id
             LEFT JOIN {flag} fl ON fc.fid = fl.fid
             ORDER BY c.cid ASC';
  return db_query($query)->fetchAllAssoc('cid');
}

function spam_detect_composite_get_node_comments_from_all_comments(array $comments, $nid) {
  return array_filter(
    $comments,
    function ($obj) use ($nid) {
      if (isset($obj->nid) && ($obj->nid == $nid)) {
        return TRUE;
      }
      return FALSE;
    }
  );
}

function spam_detect_composite_get_spammy_tld_list() {
  $spammy_tld_list = explode("\n", strtolower(variable_get('spam_detect_composite_tld_list')));

  // the array walk is to make sure that the tlds in the list
  // do not have a '.' or ' ' before or after them
  array_walk(
    $spammy_tld_list,
    function (&$tld) {
      $tld = trim($tld, ' .');
    }
  );
  return $spammy_tld_list;
}

function spam_detect_composite_get_tld_from_link($link) {
  if (!class_exists('Pdp\Parser')) return FALSE;
  $pslManager = new Pdp\PublicSuffixListManager();
  $parser     = new Pdp\Parser($pslManager->getList());

  $url = $parser->parseUrl($link);
  return $tlds[] = $url->host->publicSuffix;
}

function spam_detect_composite_get_words_chars_list() {
  $words_chars_list = explode("\n", strtolower(variable_get('spam_detect_composite_words_characters_list')));
  return $words_chars_list = array_map('trim', $words_chars_list);
}

function spam_detect_composite_get_vars() {
  return $vars = (object) array(
    'links_in_body_score'        => (object) array(
      'threshold' => variable_get('spam_detect_composite_link_body_count'),
      'increase'  => variable_get('spam_detect_composite_link_body_count_increase_spamminess'),
      'decrease'  => variable_get('spam_detect_composite_link_body_count_decrease_spamminess'),
    ),
    'body_length_score'          => (object) array(
      'threshold' => variable_get('spam_detect_composite_body_length_threshold'),
      'increase'  => variable_get('spam_detect_composite_body_length_increase_spamminess'),
      'decrease'  => variable_get('spam_detect_composite_body_length_decrease_spamminess'),
    ),
    'status_of_previous_comment' => (object) array(
      'increase' => variable_get('spam_detect_composite_status_of_previous_comments_increase'),
      'decrease' => variable_get('spam_detect_composite_status_of_previous_comments_decrease'),
      'flag'     => variable_get('spam_detect_composite_spam_flag_name'),
    ),
    'url_words_characters'       => (object) array(
      'increase'         => variable_get('spam_detect_composite_words_characters_increase'),
      'words_chars_list' => spam_detect_composite_get_words_chars_list(),
    ),
    'tlds'                       => (object) array(
      'increase'        => variable_get('spam_detect_composite_tld_increase'),
      'spammy_tld_list' => spam_detect_composite_get_spammy_tld_list(),
    ),
    'url_length'                 => (object) array(
      'increase'  => variable_get('spam_detect_composite_url_length_increase'),
      'threshold' => variable_get('spam_detect_composite_url_length_threshold'),
    ),
    'first_word'                 => (object) array(
      'increase'        => variable_get('spam_detect_composite_first_word_increase'),
      'first_word_list' => variable_get('spam_detect_composite_first_word_list'),
    ),
    'author_name_check'          => (object) array(
      'increase' => variable_get('spam_detect_composite_author_name_check'),
    ),
    'body_in_previous_comment'   => (object) array(
      'increase' => variable_get('spam_detect_composite_body_in_previous_comment'),
    ),
    'consonants'                 => (object) array(
      'increase' => variable_get('spam_detect_composite_consonants_increase'),
    ),
    'calculate_combined_score'   => (object) array(
      'threshold' => variable_get('spam_detect_composite_score_threshold'),
    ),
  );
}
