import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor, sensor
from esphome.const import (
    CONF_RESTORE,
    CONF_INITIAL_VALUE,
    STATE_CLASS_TOTAL_INCREASING,
)

CONF_BINARY_SENSOR_ID = "binary_sensor_id"
CONF_MIN_SAVE_INTERVAL = "min_save_interval"

total_count_ns = cg.esphome_ns.namespace("total_count")

TotalCount = total_count_ns.class_("TotalCount", sensor.Sensor, cg.Component)


CONFIG_SCHEMA = (
    sensor.sensor_schema(
        TotalCount,
        state_class=STATE_CLASS_TOTAL_INCREASING,
    )
    .extend(
        {
            cv.Required(CONF_BINARY_SENSOR_ID): cv.use_id(binary_sensor.BinarySensor),
            cv.Optional(CONF_INITIAL_VALUE, default=0): cv.positive_int,
            cv.Optional(CONF_RESTORE, default=True): cv.boolean,
            cv.Optional(
                CONF_MIN_SAVE_INTERVAL, default="0s"
            ): cv.positive_time_period_milliseconds,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)

    sens = await cg.get_variable(config[CONF_BINARY_SENSOR_ID])
    cg.add(var.set_parent(sens))
    cg.add(var.set_restore(config[CONF_RESTORE]))
    cg.add(var.set_min_save_interval(config[CONF_MIN_SAVE_INTERVAL]))
    cg.add(var.set_initial_value(config[CONF_INITIAL_VALUE]))
