import json
import time
import dash_pb2
import datetime
import math
from DashClient import DashClient
from MediaClient import MediaClient

config_file = 'config.json'

if __name__ == '__main__':

	with open(config_file) as data_file:
		config = json.load(data_file)

	dash = DashClient(config['dash'])
	mediaClient = MediaClient(config['media'])

	begin = datetime.datetime.now()
	total = 0

	RPM_MIN = 1000
	RPM_MAX = 11000

	GEAR_MIN = 1
	GEAR_MAX = 7

	SPEED_MAX = 220

	BATTERY_VOLTAGE_MIN = 12.0
	BATTERY_VOLTAGE_MAX = 14.0

	COOLANT_TEMPERATURE_MIN = 60.0
	COOLANT_TEMPERATURE_MAX = 100.0

	AIR_INTAKE_TEMPERATURE_MIN = 35.0
	AIR_INTAKE_TEMPERATURE_MAX = 40.0

	MANIFOLD_PRESSURE_MIN = 10.0
	MANIFOLD_PRESSURE_MAX = 100.0

	THROTTLE_POSITION_SENSOR_MIN = 0.0
	THROTTLE_POSITION_SENSOR_MAX = 100.0

	INJECTOR_DURATION_MIN = 0.0
	INJECTOR_DURATION_MAX = 0.25

	IGNITION_ADVANCE_MIN = 0.0
	IGNITION_ADVANCE_MAX = 6.0

	dashData = dash_pb2.DashData(
				speed=0,
				rpm=1000,
				gear=1,
				neutral=False,
				engineRunning=True
			)

	dashExtendedData = dash_pb2.DashExtendedData(
				batteryVoltage=0,
				coolantTemperature=0.0,
				airIntakeTemperature=0.0,
				manifoldPressure=0.0,
				throttlePositionSensor=0.0,
				injectorDuration=0.0,
				ignitionAdvance=0.0,
				kickstand=True
			)

	playStatus = dash_pb2.PlayStatus(playStatus='Example Status')

	mediaItem = dash_pb2.MediaItem(
				title='Example Title',
				artist='Example Artist',
				album='Example Album'
			)

	mediaClient.MediaChanged(mediaItem)
	mediaClient.PlayStatusChanged(playStatus)

	while True:
		now = datetime.datetime.now()
		total = (now - begin).total_seconds();
		pos = (1 + math.cos(total/2))/2
		dashData.rpm = int(RPM_MIN + pos * (RPM_MAX - RPM_MIN))
		dashData.speed = pos * SPEED_MAX
		dashData.gear = int(GEAR_MIN + pos * (GEAR_MAX - GEAR_MIN))

		try:
			dash.UpdateDashData(dashData);
		except:
			pass

		dashExtendedData.batteryVoltage = BATTERY_VOLTAGE_MIN + pos * (BATTERY_VOLTAGE_MAX - BATTERY_VOLTAGE_MIN)
		dashExtendedData.coolantTemperature = COOLANT_TEMPERATURE_MIN + pos * (COOLANT_TEMPERATURE_MAX - COOLANT_TEMPERATURE_MIN)
		dashExtendedData.airIntakeTemperature = AIR_INTAKE_TEMPERATURE_MIN + pos * (AIR_INTAKE_TEMPERATURE_MAX - AIR_INTAKE_TEMPERATURE_MIN)
		dashExtendedData.manifoldPressure = MANIFOLD_PRESSURE_MIN + pos * (MANIFOLD_PRESSURE_MAX - MANIFOLD_PRESSURE_MIN)
		dashExtendedData.throttlePositionSensor = THROTTLE_POSITION_SENSOR_MIN + pos * (THROTTLE_POSITION_SENSOR_MAX - THROTTLE_POSITION_SENSOR_MIN)
		dashExtendedData.injectorDuration = INJECTOR_DURATION_MIN + pos * (INJECTOR_DURATION_MAX - INJECTOR_DURATION_MIN)
		dashExtendedData.ignitionAdvance = IGNITION_ADVANCE_MIN + pos * (IGNITION_ADVANCE_MAX - IGNITION_ADVANCE_MIN)

		try:
			dash.UpdateDashExtendedData(dashExtendedData);
		except:
			pass

		time.sleep(0.016)

