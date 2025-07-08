import esphome.codegen as cg
from esphome.components import button
import esphome.config_validation as cv
from esphome.const import CONF_ID

from .. import CONF_TOTAL_COUNT_ID, TOTAL_COUNT_COMPONENT_SCHEMA, total_count_ns

DEPENDENCIES = ["total_count"]

CODEOWNERS = ["@syssi"]

CONF_RESET_COUNTER = "reset_counter"

TotalCountButton = total_count_ns.class_(
    "TotalCountButton", button.Button, cg.Component
)

CONFIG_SCHEMA = TOTAL_COUNT_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(CONF_RESET_COUNTER): button.button_schema(
            TotalCountButton, icon="mdi:keyboard-tab-reverse"
        ).extend(cv.COMPONENT_SCHEMA),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_TOTAL_COUNT_ID])
    for key in [CONF_RESET_COUNTER]:
        if key in config:
            conf = config[key]
            var = cg.new_Pvariable(conf[CONF_ID])
            await cg.register_component(var, conf)
            await button.register_button(var, conf)
            cg.add(var.set_parent(hub))
