import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import STATE_CLASS_TOTAL_INCREASING, UNIT_EMPTY

from . import CONF_TOTAL_COUNT_ID, TOTAL_COUNT_COMPONENT_SCHEMA

CODEOWNERS = ["@syssi"]

CONF_TOTAL_COUNT = "total_count"

SENSOR_DEFS = {
    CONF_TOTAL_COUNT: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": "mdi:counter",
        "accuracy_decimals": 0,
        "state_class": STATE_CLASS_TOTAL_INCREASING,
    },
}

CONFIG_SCHEMA = TOTAL_COUNT_COMPONENT_SCHEMA.extend(
    {
        cv.Required(key): sensor.sensor_schema(**kwargs)
        for key, kwargs in SENSOR_DEFS.items()
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_TOTAL_COUNT_ID])
    for key in SENSOR_DEFS:
        if key in config:
            sens = await sensor.new_sensor(config[key])
            cg.add(getattr(hub, f"set_{key}_sensor")(sens))
