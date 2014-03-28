<?php
/**
 * @file
 * spam_detect_composite_example.rules_defaults.inc
 */


/**
 * Implements hook_default_rules_configuration().
 */
function spam_detect_composite_example_default_rules_configuration() {
  $items = array();
  $items['rules_identify_spam'] = entity_import('rules_config', '{ "rules_identify_spam" : {
      "LABEL" : "Identify spam",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "flag", "comment" ],
      "ON" : { "comment_insert" : [] },
      "IF" : [
        { "text_or_context_is_spammy" : { "text" : [ "comment:comment-body:value" ], "node" : [ "comment:node" ] } }
      ],
      "DO" : [
        { "flag_flagcomment" : {
            "flag" : "is_spam",
            "comment" : [ "comment" ],
            "flagging_user" : [ "comment:node:author" ],
            "permission_check" : 1
          }
        }
      ]
    }
  }');
  return $items;
}

