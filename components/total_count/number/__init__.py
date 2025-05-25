import esphome.codegen as cg
from esphome.components import number
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_MAX_VALUE,
    CONF_MIN_VALUE,
    CONF_MODE,
    CONF_STEP,
    ENTITY_CATEGORY_CONFIG,
    ICON_EMPTY,
    UNIT_EMPTY,
)

from .. import CONF_TOTAL_COUNT_ID, TotalCount, total_count_ns

DEPENDENCIES = ["total_count"]

CODEOWNERS = ["@syssi"]

CONF_TOTAL_COUNT = "total_count"

TotalCountNumber = total_count_ns.class_(
    "TotalCountNumber", number.Number, cg.Component
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_TOTAL_COUNT_ID): cv.use_id(TotalCount),
        cv.Optional(CONF_TOTAL_COUNT): number.number_schema(
            TotalCountNumber,
            icon=ICON_EMPTY,
            entity_category=ENTITY_CATEGORY_CONFIG,
            unit_of_measurement=UNIT_EMPTY,
        )
        .extend(
            {
                cv.Optional(CONF_STEP, default=1): cv.float_,
                cv.Optional(CONF_MODE, default="BOX"): cv.enum(
                    number.NUMBER_MODES, upper=True
                ),
                cv.Optional(CONF_MIN_VALUE, default=0): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=4294967295): cv.float_,
            }
        )
        .extend(cv.COMPONENT_SCHEMA),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_TOTAL_COUNT_ID])
    for key in [CONF_TOTAL_COUNT]:
        if key in config:
            conf = config[key]
            var = cg.new_Pvariable(conf[CONF_ID])
            await cg.register_component(var, conf)
            await number.register_number(
                var,
                conf,
                min_value=conf[CONF_MIN_VALUE],
                max_value=conf[CONF_MAX_VALUE],
                step=conf[CONF_STEP],
            )
            cg.add(getattr(hub, f"set_{key}_number")(var))
            cg.add(var.set_parent(hub))
