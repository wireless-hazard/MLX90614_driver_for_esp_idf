set(COMPONENT_SRCS
    "src/MLX90614_API.c"
    "src/MLX90614_SMBus_Driver.c")

set(COMPONENT_ADD_INCLUDEDIRS "include")

set(COMPONENT_PRIV_REQUIRES main "I2Cbus")

register_component(MLX90614_component)

component_compile_options(PUBLIC -DMPU_COMPONENT_TRUE=1)
