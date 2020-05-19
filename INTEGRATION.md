# Rockette 🚀

## Integration

If you are not familiar with gRPC, it's a great idea to go through [their documentation](https://grpc.io/docs/quickstart/).

The `proto` file that describes the gRPC interfaces available on Rockette is `src/proto/dash.proto`.

By default, the `DashService` service binds to all interfaces on port `50051`, but this can be changed in the `config.json` file.

## Examples

There are basic integration examples in the `integration/examples` directory.