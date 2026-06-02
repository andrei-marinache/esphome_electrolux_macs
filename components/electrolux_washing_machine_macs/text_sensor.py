import esphome.codegen as cg
from esphome.components import text_sensor
import esphome.config_validation as cv
from esphome.const import (
    ENTITY_CATEGORY_DIAGNOSTIC,
)

from . import CONF_ELECTROLUX_WASHING_MACHINE_MACS_ID, ElectroluxWashingMachineMacsComponent

CONF_SELECTED_PROGRAM_NAME = "selected_program_name"
CONF_ACTIVE_ALARM = "active_alarm"

TYPES = [
    CONF_SELECTED_PROGRAM_NAME,
    CONF_ACTIVE_ALARM
]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_ELECTROLUX_WASHING_MACHINE_MACS_ID): cv.use_id(ElectroluxWashingMachineMacsComponent),
        cv.Optional(CONF_SELECTED_PROGRAM_NAME): text_sensor.text_sensor_schema(),
        cv.Optional(CONF_ACTIVE_ALARM): text_sensor.text_sensor_schema(
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC
        )
    }
).extend(cv.COMPONENT_SCHEMA)


async def setup_conf(config, key, hub):
    if sensor_config := config.get(key):
        sens = await text_sensor.new_text_sensor(sensor_config)
        cg.add(getattr(hub, f"set_{key}_text_sensor")(sens))


async def to_code(config):
    hub = await cg.get_variable(config[CONF_ELECTROLUX_WASHING_MACHINE_MACS_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)

