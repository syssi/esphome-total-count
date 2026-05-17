"""Schema structure tests for total_count ESPHome component modules."""

import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

import components.total_count as hub  # noqa: E402
from components.total_count import sensor  # noqa: E402


class TestHubConstants:
    def test_conf_ids_defined(self):
        assert hub.CONF_TOTAL_COUNT_ID == "total_count_id"
        assert hub.CONF_BINARY_SENSOR_ID == "binary_sensor_id"


class TestSensorDefs:
    def test_sensor_defs_completeness(self):
        assert sensor.CONF_TOTAL_COUNT in sensor.SENSOR_DEFS
        assert len(sensor.SENSOR_DEFS) == 1

    def test_sensor_defs_keys_match_schema(self):
        assert set(sensor.SENSOR_DEFS.keys()) == {sensor.CONF_TOTAL_COUNT}

    def test_sensor_keys_are_strings(self):
        for key in sensor.SENSOR_DEFS:
            assert isinstance(key, str)
