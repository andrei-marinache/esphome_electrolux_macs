import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from ..electrolux_macs import CONFIG_SCHEMA_BASE, to_code_base as to_code

CODEOWNERS = ["@agocsdaniel"]

MULTI_CONF = True

AUTO_LOAD = ["electrolux_macs", "binary_sensor", "sensor", "text_sensor"]

CONF_ELECTROLUX_DRYER_MACS_ID = "electrolux_dryer_macs_id"

electrolux_dryer_macs_ns = cg.esphome_ns.namespace("electrolux_dryer_macs")
ElectroluxDryerMacsComponent = electrolux_dryer_macs_ns.class_(
    "ElectroluxDryerMacsComponent", cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = CONFIG_SCHEMA_BASE.extend({
    cv.GenerateID(): cv.declare_id(ElectroluxDryerMacsComponent),
})

