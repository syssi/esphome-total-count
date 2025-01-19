import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_INITIAL_VALUE, CONF_RESTORE, CONF_STEP

CODEOWNERS = ["@syssi"]

AUTO_LOAD = ["binary_sensor", "button", "number", "sensor"]
MULTI_CONF = True

CONF_TOTAL_COUNT_ID = "total_count_id"
CONF_BINARY_SENSOR_ID = "binary_sensor_id"
CONF_MIN_SAVE_INTERVAL = "min_save_interval"

total_count_ns = cg.esphome_ns.namespace("total_count")
TotalCount = total_count_ns.class_("TotalCount", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(TotalCount),
        cv.Required(CONF_BINARY_SENSOR_ID): cv.use_id(binary_sensor.BinarySensor),
        cv.Optional(CONF_INITIAL_VALUE, default=0): cv.positive_int,
        cv.Optional(CONF_STEP, default=1): cv.positive_int,
        cv.Optional(CONF_RESTORE, default=True): cv.boolean,
        cv.Optional(
            CONF_MIN_SAVE_INTERVAL, default="0s"
        ): cv.positive_time_period_milliseconds,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    sens = await cg.get_variable(config[CONF_BINARY_SENSOR_ID])
    cg.add(var.set_parent(sens))
    cg.add(var.set_restore(config[CONF_RESTORE]))
    cg.add(var.set_min_save_interval(config[CONF_MIN_SAVE_INTERVAL]))
    cg.add(var.set_initial_value(config[CONF_INITIAL_VALUE]))
    cg.add(var.set_step(config[CONF_STEP]))
