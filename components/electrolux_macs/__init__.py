from esphome import pins
import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_RECEIVE_TIMEOUT, CONF_UART_ID

MULTI_CONF = True

DEPENDENCIES = ["uart"]

CODEOWNERS = ["@agocsdaniel"]

CONF_ELECTROLUX_MACS_ID = "electrolux_macs_id"

CONF_VERIFY_CHECKSUM = "verify_checksum"

electrolux_macs_ns = cg.esphome_ns.namespace("electrolux_macs")
ElectroluxMacsComponent = electrolux_macs_ns.class_(
    "ElectroluxMacsComponent", cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA_BASE = cv.Schema(
    {
        cv.Optional(CONF_RECEIVE_TIMEOUT, default="200ms"): cv.positive_time_period_milliseconds,
        cv.Optional(CONF_VERIFY_CHECKSUM, default=True): cv.boolean,
    }
).extend(uart.UART_DEVICE_SCHEMA)

async def to_code_base(config):
    uart_component = await cg.get_variable(config[CONF_UART_ID])
    var = cg.new_Pvariable(config[CONF_ID], uart_component)
    cg.add(var.set_receive_timeout(config[CONF_RECEIVE_TIMEOUT].total_milliseconds))
    cg.add(var.set_verify_checksum(config[CONF_VERIFY_CHECKSUM]))
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

