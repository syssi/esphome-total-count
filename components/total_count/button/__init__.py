import esphome.codegen as cg
from esphome.components import button
import esphome.config_validation as cv
from esphome.const import CONF_ICON, CONF_ID

from .. import CONF_TOTAL_COUNT_ID, TotalCount, total_count_ns

DEPENDENCIES = ["total_count"]

CODEOWNERS = ["@syssi"]

CONF_RESET_COUNTER = "reset_counter"

ICON_RESET_COUNTER = "mdi:keyboard-tab-reverse"

BUTTONS = [
    CONF_RESET_COUNTER,
]

TotalCountButton = total_count_ns.class_(
    "TotalCountButton", button.Button, cg.Component
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_TOTAL_COUNT_ID): cv.use_id(TotalCount),
        cv.Optional(CONF_RESET_COUNTER): button.BUTTON_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(TotalCountButton),
                cv.Optional(CONF_ICON, default=ICON_RESET_COUNTER): cv.icon,
            }
        ).extend(cv.COMPONENT_SCHEMA),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_TOTAL_COUNT_ID])
    for key in BUTTONS:
        if key in config:
            conf = config[key]
            var = cg.new_Pvariable(conf[CONF_ID])
            await cg.register_component(var, conf)
            await button.register_button(var, conf)
            cg.add(var.set_parent(hub))
