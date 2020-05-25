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

	hostname = socket.gethostname()
	ip_address = socket.gethostbyname(hostname)

	floatData = rkt_pb2.FloatValue(
				value=0,
				identifier='speed',
			)

	RPM_MIN = 1500
	RPM_MAX = 11000
	TEMP_MIN = 90
	TEMP_MAX = 105
	SPEED_MAX = 299
	THROTTLE_MAX = 100

	while True:
		now = datetime.datetime.now()
		total = (now - begin).total_seconds()
		pos = (1 + math.cos(total/2))/2

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
		except:
			pass
		time.sleep(0.016)


