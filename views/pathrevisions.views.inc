<?php
/**
 * @file
 * Views integration for pathrevisions.
 */

/**
 * Implements hook_views_handlers().
 *
function pathrevisions_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'pathrevisions') . '/views/handlers',
    ),
    'handlers' => array(
      'pathrevisions_views_handler_field_alias' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}
*/

/**
 * Implements hook_views_data().
 */
function pathrevisions_views_data() {
  $data['path_revisions']['table']['group'] = t('Content revision');

  // Advertise this table as a possible base table
  $data['path_revisions']['table']['base'] = array(
    'field' => 'vid',
    'title' => t('Node revision path alias'),
    'help' => t('Path alias revisions are a history of changes to node path alias.'),
  );

  $data['path_revisions']['table']['join'] = array(
    // Directly links to node_revision table.
    'node_revision' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
    'node' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
  );

  // vid field
  $data['path_revisions']['vid'] = array(
    'title' => t('Vid'),
    'help' => t('The node revision path alias.'), // The help that appears on the UI,
    // Information for displaying the nid
    'field' => array(
      //      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    // Information for accepting a nid as an argument
    'argument' => array(
      'handler' => 'views_handler_argument_node_vid',
      'parent' => 'views_handler_argument_numeric', // make sure parent is included
      'click sortable' => TRUE,
      'numeric' => TRUE,
    ),
    // Information for accepting a nid as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // Information for sorting on a nid.
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'node',
      'base field' => 'nid',
      'title' => t('Node'),
      'label' => t('Get the actual node from a node revision.'),
    ),
  );

  // alias field.
  $data['path_revisions']['alias'] = array(
    'group' => t('Content revision'),
    'title' => t('Path alias'),
    'help' => t('The path alias of this content revision.'),
    'field' => array(
      'handler' => 'views_handler_field_node_path',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
  );

  // timestamp field.
  $data['path_revisions']['timestamp'] = array(
    'group' => t('Content revision'),
    'title' => t('Path updated date'),
    'help' => t('The date the path alias was last updated.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  return $data;
}

/**
  * Implements hook_views_data_alter().
  */
function pathrevisions_views_data_alter(&$data) {
  $data['node_revision']['table']['join']['path_revisions'] = array(
    // this explains how the 'node' table (named in the line above)
    // links toward the path_revisions table.
    'handler' => 'views_join', // this is actually optional
    'left_table' => 'path_revisions', // Because this is a direct link it could be left out.
    'left_field' => 'vid',
    'field' => 'vid',
  );

  $data['node']['table']['join']['path_revisions'] = array(
    // this explains how the 'node' table (named in the line above)
    // links toward the path_revisions table.
    'handler' => 'views_join', // this is actually optional
    'left_table' => 'path_revisions', // Because this is a direct link it could be left out.
    'left_field' => 'vid',
    'field' => 'vid',
  );
}
