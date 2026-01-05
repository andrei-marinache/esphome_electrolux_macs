import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_POWER,
    DEVICE_CLASS_RUNNING,
    DEVICE_CLASS_DOOR,
)

from . import CONF_ELECTROLUX_WASHING_MACHINE_MACS_ID, ElectroluxWashingMachineMacsComponent

CONF_POWERED_ON = "powered_on"
CONF_RUNNING = "running"
CONF_DOOR_LOCKED = "door_locked"
CONF_PRE_WASH_ENABLED = "pre_wash_enabled"
CONF_STAIN_WASH = "stain_wash"
CONF_EXTRA_RINSE = "extra_rinse"
CONF_SOFT_PLUS = "soft_plus"
CONF_EASY_IRON = "easy_iron"

TYPES = [
    CONF_POWERED_ON,
    CONF_RUNNING,
    CONF_DOOR_LOCKED,
    CONF_PRE_WASH_ENABLED,
    CONF_STAIN_WASH,
    CONF_EXTRA_RINSE,
    CONF_SOFT_PLUS,
    CONF_EASY_IRON,
]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_ELECTROLUX_WASHING_MACHINE_MACS_ID): cv.use_id(ElectroluxWashingMachineMacsComponent),
        cv.Optional(CONF_POWERED_ON): binary_sensor.binary_sensor_schema(
            device_class=DEVICE_CLASS_POWER
        ),
        cv.Optional(CONF_RUNNING): binary_sensor.binary_sensor_schema(
            device_class=DEVICE_CLASS_RUNNING,
        ),
        cv.Optional(CONF_DOOR_LOCKED): binary_sensor.binary_sensor_schema(
            device_class=DEVICE_CLASS_DOOR,
        ),
        cv.Optional(CONF_PRE_WASH_ENABLED): binary_sensor.binary_sensor_schema(
        ),
        cv.Optional(CONF_STAIN_WASH): binary_sensor.binary_sensor_schema(
        ),
        cv.Optional(CONF_EXTRA_RINSE): binary_sensor.binary_sensor_schema(
        ),
        cv.Optional(CONF_SOFT_PLUS): binary_sensor.binary_sensor_schema(
        ),
        cv.Optional(CONF_EASY_IRON): binary_sensor.binary_sensor_schema(
        ),
    }
).extend(cv.COMPONENT_SCHEMA)


async def setup_conf(config, key, hub):
    if sensor_config := config.get(key):
        var = await binary_sensor.new_binary_sensor(sensor_config)
        cg.add(getattr(hub, f"set_{key}_binary_sensor")(var))


async def to_code(config):
    hub = await cg.get_variable(config[CONF_ELECTROLUX_WASHING_MACHINE_MACS_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)
