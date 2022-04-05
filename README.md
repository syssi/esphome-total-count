# esphome-total-count

![GitHub actions](https://github.com/syssi/esphome-total-count/actions/workflows/ci.yaml/badge.svg)
![GitHub stars](https://img.shields.io/github/stars/syssi/esphome-total-count)
![GitHub forks](https://img.shields.io/github/forks/syssi/esphome-total-count)
![GitHub watchers](https://img.shields.io/github/watchers/syssi/esphome-total-count)
[!["Buy Me A Coffee"](https://img.shields.io/badge/buy%20me%20a%20coffee-donate-yellow.svg)](https://www.buymeacoffee.com/syssi)

The total count sensor allows you to count the number of state changes of a binary sensor

```
# Example configuration entry

external_components:
  - source: github://syssi/esphome-total-count@main

sensor:
  - platform: total_count
    name: "Total count"
    binary_sensor_id: barrier
```

## Configuration variables

- **binary_sensor_id** (**Required**): The binary sensor to count state changes on.
- **name** (**Required**, string): The name of the sensor.
- **id** (*Optional*): Manually specify the ID used for code generation.
- **restore** (*Optional*, boolean): Whether to store the intermediate result on the device so
  that the value can be restored upon power cycle or reboot.
  Defaults to ``true``.
- **min_save_interval** (*Optional*, `config-time`): The minimum time span between saving updated values to storage. This is to keep wearout of memory low. Defaults to ``0s``.
- **initial_value** (*Optional*, float): The value to set the state to on setup if not
  restored with ``restore_value``.
- All other options from `Sensor`.

## References

- https://github.com/esphome/issues/issues/664
- https://github.com/esphome/issues/issues/663
