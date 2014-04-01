<?php

function spam_detect_composite_links_in_body_score($link_count, $increase, $decrease, $threshold) {
  if ($threshold < 0) return 0; // Filter is set to off: -1
  if ($link_count < $threshold) return -$decrease;
  if ($link_count >= $threshold) return $link_count * $increase;
}

function spam_detect_composite_body_length_score($text, $link_count, $increase, $decrease, $threshold) {
  if ($threshold < 0) return 0; // Filter is set to off: -1
  $length = strlen(str_replace(' ', '', $text));
  if (($length > $threshold) && ($link_count == 0)) return -$decrease;
  if ($length < $threshold) return $increase;
  return 0;
}

function spam_detect_composite_status_of_previous_comment(
  stdClass $comment,
  stdClass $last_comment,
  $increase,
  $decrease,
  $flag
) {
  if ($increase <= 0) return 0;
  if ($last_comment->email == $comment->email) {
    return ($comment->flag_name == trim($flag)) ? $increase : -$decrease;
  }
  return 0;
}

function spam_detect_composite_url_words_characters($link, $increase, array $words_chars_list) {
  if ($increase <= 0) return 0; // Filter set to off: -1
  $spam_score = array(0);
  foreach ($words_chars_list as $word_char) {
    $spam_score[] = $increase * substr_count($link, $word_char);
  }
  return array_sum($spam_score);
}

function spam_detect_composite_tlds($link, $increase, array $spammy_tld_list) {
  if ($increase <= 0) return 0;
  $tld = spam_detect_composite_get_tld_from_link($link);
  if ($tld === FALSE) return 0;
  if (in_array($tld, $spammy_tld_list)) return $increase;
  return 0;
}

function spam_detect_composite_url_length($link, $increase, $threshold) {
  if ($threshold < 0) return 0;
  $url_length = strlen(str_replace(array('http://', 'https://'), '', $link));
  if ($url_length > $threshold) return $increase;
  return 0;
}

function spam_detect_composite_first_word($text, $increase, $first_word_list) {
  if ($increase <= 0) return 0; // filter set to off

  $spammy_words = strtolower($first_word_list);
  $spammy_words = array_map('trim', explode("\n", $spammy_words));

  $first_word = strtolower(strtok($text, ' '));
  $first_word = preg_replace('/[^A-Za-z0-9\-]/', '', $first_word); // remove special chars
  if (in_array($first_word, $spammy_words)) return $increase;
  return 0;
}

function spam_detect_composite_author_name_check($name, $increase) {
  if ($increase <= 0) return 0;
  $needles = array('http://', 'https://');
  foreach ($needles as $search) {
    $count[] = substr_count($name, $search);
  }
  return array_sum($count) * $increase;
}

//todo this may need to be changed to where it is checking the author and seeing if they are using the same body...
function spam_detect_composite_body_in_previous_comment(stdClass $comment, stdClass $last_comment, $increase) {
  if ($increase <= 0) return 0;
  if (trim($last_comment->body) == trim($comment->body)) return $increase;
  return 0;
}

function spam_detect_composite_consonants($text, $increase) {
  if ($increase <= 0) return 0; // Filter set to off: -1
  preg_match_all('/[bcdfghjklmnpqrstvwxz]{5}/i', $text, $matches); // matches 6 or more consonants
  return $spam_score = count($matches[0]) * $increase;
}
