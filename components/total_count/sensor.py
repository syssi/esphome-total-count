import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import STATE_CLASS_TOTAL_INCREASING, UNIT_EMPTY

from . import CONF_TOTAL_COUNT_ID, TotalCount

CONF_TOTAL_COUNT = "total_count"

ICON_TOTAL_COUNT = "mdi:counter"

SENSORS = [
    CONF_TOTAL_COUNT,
]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_TOTAL_COUNT_ID): cv.use_id(TotalCount),
        cv.Required(CONF_TOTAL_COUNT): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_TOTAL_COUNT,
            accuracy_decimals=0,
            state_class=STATE_CLASS_TOTAL_INCREASING,
        ),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_TOTAL_COUNT_ID])
    for key in SENSORS:
        if key in config:
            conf = config[key]
            sens = await sensor.new_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_sensor")(sens))
