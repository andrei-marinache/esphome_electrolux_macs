import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from ..electrolux_macs import CONFIG_SCHEMA_BASE, CONF_ID, CONF_UART_ID, CONF_RECEIVE_TIMEOUT, CONF_VERIFY_CHECKSUM

CODEOWNERS = ["@agocsdaniel"]

MULTI_CONF = True

AUTO_LOAD = ["electrolux_macs", "binary_sensor", "sensor", "text_sensor"]

CONF_ELECTROLUX_WASHING_MACHINE_MACS_ID = "electrolux_washing_machine_macs_id"

CONF_MOTOR_DRUM_RATIO = "motor_drum_ratio"
CONF_START_DELAY_INDEX = "start_delay_index"

electrolux_washing_machine_macs_ns = cg.esphome_ns.namespace("electrolux_washing_machine_macs")
ElectroluxWashingMachineMacsComponent = electrolux_washing_machine_macs_ns.class_(
    "ElectroluxWashingMachineMacsComponent", cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = CONFIG_SCHEMA_BASE.extend({
    cv.GenerateID(): cv.declare_id(ElectroluxWashingMachineMacsComponent),
    cv.Optional(CONF_MOTOR_DRUM_RATIO, default=12.2): cv.float_range(0, 100),
    # Byte of the program set frame holding the start delay (x30 min): 9 on EWX14 washers, 11 on EW8W261B washer-dryers
    cv.Optional(CONF_START_DELAY_INDEX, default=9): cv.int_range(4, 12),
})

async def to_code(config):
    uart_component = await cg.get_variable(config[CONF_UART_ID])
    var = cg.new_Pvariable(config[CONF_ID], uart_component)
    cg.add(var.set_receive_timeout(config[CONF_RECEIVE_TIMEOUT].total_milliseconds))
    cg.add(var.set_verify_checksum(config[CONF_VERIFY_CHECKSUM]))
    cg.add(var.set_motor_drum_ratio(config[CONF_MOTOR_DRUM_RATIO]))
    cg.add(var.set_start_delay_index(config[CONF_START_DELAY_INDEX]))
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

