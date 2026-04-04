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


class TestSensorConstants:
    def test_conf_total_count_defined(self):
        assert sensor.CONF_TOTAL_COUNT == "total_count"
