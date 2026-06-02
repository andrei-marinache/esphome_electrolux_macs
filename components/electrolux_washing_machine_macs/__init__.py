import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from ..electrolux_macs import CONFIG_SCHEMA_BASE, to_code_base as to_code

CODEOWNERS = ["@agocsdaniel"]

MULTI_CONF = True

AUTO_LOAD = ["electrolux_macs", "binary_sensor", "sensor", "text_sensor"]

CONF_ELECTROLUX_WASHING_MACHINE_MACS_ID = "electrolux_washing_machine_macs_id"

CONF_MOTOR_DRUM_RATIO = "motor_drum_ratio"

TYPES = [
	CONF_MOTOR_DRUM_RATIO,
]

electrolux_washing_machine_macs_ns = cg.esphome_ns.namespace("electrolux_washing_machine_macs")
ElectroluxWashingMachineMacsComponent = electrolux_washing_machine_macs_ns.class_(
    "ElectroluxWashingMachineMacsComponent", cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = CONFIG_SCHEMA_BASE.extend({
    cv.GenerateID(): cv.declare_id(ElectroluxWashingMachineMacsComponent),
    cv.Optional(CONF_MOTOR_DRUM_RATIO): cv.float_range(0, 100),
})

