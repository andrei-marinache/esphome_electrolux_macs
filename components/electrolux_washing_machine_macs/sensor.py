import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    ICON_TIMER,
    STATE_CLASS_MEASUREMENT,
    DEVICE_CLASS_DURATION,
    DEVICE_CLASS_MOISTURE,
    DEVICE_CLASS_SPEED,
    DEVICE_CLASS_TEMPERATURE,
    UNIT_CELSIUS,
    UNIT_MINUTE,
    UNIT_REVOLUTIONS_PER_MINUTE,
)

from . import CONF_ELECTROLUX_WASHING_MACHINE_MACS_ID, ElectroluxWashingMachineMacsComponent

CONF_REMAINING_TIME = "remaining_time"
CONF_START_DELAY_TIME = "start_delay_time"
CONF_SELECTED_PROGRAM_NUMBER = "selected_program_number"
CONF_TIME_MANAGER = "time_manager"
CONF_WASH_TEMPERATURE = "wash_temperature"
CONF_SPIN_SPEED = "spin_speed"

TYPES = [
    CONF_REMAINING_TIME,
    CONF_START_DELAY_TIME,
    CONF_SELECTED_PROGRAM_NUMBER,
    CONF_TIME_MANAGER,
    CONF_WASH_TEMPERATURE,
    CONF_SPIN_SPEED,
]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_ELECTROLUX_WASHING_MACHINE_MACS_ID): cv.use_id(ElectroluxWashingMachineMacsComponent),
        cv.Optional(CONF_REMAINING_TIME): sensor.sensor_schema(
            unit_of_measurement=UNIT_MINUTE,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
            device_class=DEVICE_CLASS_DURATION,
            icon=ICON_TIMER,
        ),
        cv.Optional(CONF_START_DELAY_TIME): sensor.sensor_schema(
            unit_of_measurement=UNIT_MINUTE,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
            device_class=DEVICE_CLASS_DURATION,
        ),
        cv.Optional(CONF_SELECTED_PROGRAM_NUMBER): sensor.sensor_schema(
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_TIME_MANAGER): sensor.sensor_schema(
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_WASH_TEMPERATURE): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
            device_class=DEVICE_CLASS_TEMPERATURE,
        ),
        cv.Optional(CONF_SPIN_SPEED): sensor.sensor_schema(
            unit_of_measurement=UNIT_REVOLUTIONS_PER_MINUTE,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
            device_class=DEVICE_CLASS_SPEED,
        ),
    }
).extend(cv.COMPONENT_SCHEMA)


async def setup_conf(config, key, hub):
    if sensor_config := config.get(key):
        sens = await sensor.new_sensor(sensor_config)
        cg.add(getattr(hub, f"set_{key}_sensor")(sens))


async def to_code(config):
    hub = await cg.get_variable(config[CONF_ELECTROLUX_WASHING_MACHINE_MACS_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)

