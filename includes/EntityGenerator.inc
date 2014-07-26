<?php

/**
 * @file
 * Holds the class for generate any given entity.
 */

class EntityGenerator {

  /**
   * @var \EntityMetadataWrapper
   *
   * The entity wrapped with entity metadata wrapper.
   */
  protected $wrapper;

  /**
   * @var Array
   *
   * The entity info.
   */
  protected $info;

  /**
   * Constructing the class.
   *
   * @param $type
   *  The entity type that we need to construct.
   */
  public function __construct($type) {
    $this->info = entity_get_info($type);

    $values = array();

    // Set the type if needed.
    if (!empty($this->info['bundles'])) {
      $values[$this->info['entity keys']['bundle']] = array_rand($this->info['bundles']);
    }

    // Set the label of needed.
    if (!empty($this->info['entity keys']['label'])) {
    }

    // Set an owner for the entity.
    if (in_array('uid', $this->info['schema_fields_sql']['base table'])) {
    }

    $entity = entity_create($type, $values);
    $this->wrapper = entity_metadata_wrapper($type, $entity);
  }

  /**
   * Generate the properties value according to their type.
   *
   * @return $this
   */
  public function generateProperties() {
    return $this;
  }

  /**
   * Generate value for a given value.
   *
   * @param $field
   *  The name of the property.
   *
   * @return $this.
   */
  public function GenerateValue($field) {
    return $this;
  }

  /**
   * Generate fields for the new entity object using the devel generate module.
   *
   * @return $this
   */
  public function GenerateFields() {

    dpm($this->wrapper->value());

    // Attach field and their values. Using devel_generate for that.
    module_load_include('inc', 'devel_generate', 'devel_generate.fields');
//    devel_generate_fields($this->wrapper->value(), $this->wrapper->type(), $this->wrapper->getBundle());

    return $this;
  }

  /**
   * Save the object to the DB.
   *
   * @return $this.
   */
  public function save() {
    $this->wrapper->save();

    return $this->wrapper->value();
  }
}