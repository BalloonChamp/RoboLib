# RoboLib

Example framework for robot components communicating over TCP.

## Build

```bash
./scripts/build.sh
```

## Run components

In separate terminals run:

```bash
./scripts/run_motor1.sh
./scripts/run_motor2.sh
./scripts/run_sensor.sh
```

Then run main controller:

```bash
./scripts/run_main.sh
```

This demonstrates communication between the main process and each component.
