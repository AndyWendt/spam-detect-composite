<?php
/**
 * Our condition class.
 */
class SpamDetectCompositeRulesCondition extends RulesConditionHandlerBase {
  /**
   * @inheritdoc
   */
  public static function getInfo() {
    $info = array(
      'name' => 'text_or_context_is_spammy',
      'label' => t('Text or Context is spammy'),
      'help' => t(
        'Validates to TRUE if the text or context is determined to be spam by the enabled <a href="!path">Spam Detect filters and settings</a>.',
        array('!path' => url('admin/config/system/spam_detect'))
      ),
      'parameter' => array(
        'text' => array(
          'type' => 'text',
          'label' => t('Text'),
        ),
        'node' => array(
          'type' => 'node',
          'label' => t('Node')
        ),
      ),
      'group' => t('Spam detect'),
    );
    return $info;
  }

  /**
   * @inheritdoc
   */
  public function execute($text, $node) {
    return spam_detect_detect($text, $node);
  }
}
