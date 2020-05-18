import grpc
import dash_pb2
import dash_pb2_grpc

class MediaClient:
	def __init__(self, config):
		self.config = config
		self.host_string = '{0}:{1}'.format(self.config['host'], self.config['port'])

	def PlayStatusChanged(self, playStatus):
		with grpc.insecure_channel(self.host_string) as channel:
			stub = dash_pb2_grpc.MediaPlayerStub(channel)
			response = stub.PlayStatusChanged(playStatus)

	def MediaChanged(self, mediaItem):
		with grpc.insecure_channel(self.host_string) as channel:
			stub = dash_pb2_grpc.MediaPlayerStub(channel)
			response = stub.MediaChanged(mediaItem)
