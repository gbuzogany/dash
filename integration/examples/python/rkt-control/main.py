import json
import rkt_pb2
import socket
import math
import datetime
import time


from RocketteClient import RocketteClient

config_file = 'config.json'

if __name__ == '__main__':
	begin = datetime.datetime.now()

	with open(config_file) as data_file:
		config = json.load(data_file)

	rkt = RocketteClient(config)

	floatData = rkt_pb2.FloatValue(
				value=0,
				identifier='speed',
			)

	stringData = rkt_pb2.StringValue(
				value='1',
				identifier='gear',
			)

	RPM_MIN = 1500
	RPM_MAX = 11000
	GEAR_MIN = 1
	GEAR_MAX = 7
	TEMP_MIN = 90
	TEMP_MAX = 105
	SPEED_MAX = 299
	THROTTLE_MAX = 100

	while True:
		now = datetime.datetime.now()
		total = (now - begin).total_seconds()
		pos = (1 + math.cos(total/2-math.pi))/2

		try:
			floatData.value = pos * (RPM_MAX - RPM_MIN) + RPM_MIN
			floatData.identifier = 'rpm'
			rkt.UpdateFloatData(floatData)
			floatData.value = pos * SPEED_MAX
			floatData.identifier = 'speed'
			rkt.UpdateFloatData(floatData)
			floatData.value = pos * THROTTLE_MAX
			floatData.identifier = 'tps'
			rkt.UpdateFloatData(floatData)
			floatData.value = pos * (TEMP_MAX - TEMP_MIN) + TEMP_MIN
			floatData.identifier = 'temp'
			rkt.UpdateFloatData(floatData)
			stringData.value = str(math.floor(pos * (GEAR_MAX - GEAR_MIN) + GEAR_MIN))
			rkt.UpdateStringData(stringData)
		except:
			pass
		time.sleep(0.016)


