import grpc
import dash_pb2
import dash_pb2_grpc

class DashClient:
	def __init__(self, config):
		self.config = config
		self.host_string = '{0}:{1}'.format(self.config['host'], self.config['port'])

	def UpdateDashData(self, dashData):
		with grpc.insecure_channel(self.host_string) as channel:
			stub = dash_pb2_grpc.DashControlStub(channel)
			response = stub.UpdateDashData(dashData)

	def UpdateDashExtendedData(self, dashExtendedData):
		with grpc.insecure_channel(self.host_string) as channel:
			stub = dash_pb2_grpc.DashControlStub(channel)
			response = stub.UpdateDashExtendedData(dashExtendedData)
