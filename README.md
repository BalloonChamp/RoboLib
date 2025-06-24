# RoboLib

Example framework for robot components communicating over TCP.
The library now also provides an optional database based communication
model. Components can publish telemetry and receive commands through a
central `Database` process instead of connecting directly to the main
controller.

## Build

```bash
./scripts/build.sh
```

## Run

Start the main controller first. It will keep running and periodically
attempt to connect to any components that are not yet available.

```bash
./scripts/run_main.sh
```

In separate terminals start any components you wish to run:

```bash
./scripts/run_motor1.sh
./scripts/run_motor2.sh
./scripts/run_sensor.sh
```

These scripts now launch a single `robot` binary with different flags
so you can also invoke it manually. For example `./build/robot --motor 1`
starts the first motor component while `./build/robot --main` starts the
controller loop. The main loop accepts optional `--motor-port <p>` and
`--sensor-port <p>` flags which can be repeated to configure additional
components.

### Database based example

Launch the database first:

```bash
./scripts/run_database.sh
```

Then in other terminals start the database aware components and a scheduler:

```bash
./scripts/run_dbmotor1.sh
./scripts/run_dbmotor2.sh
./scripts/run_dbsensor.sh
./scripts/run_scheduler.sh
```

If you prefer to run the entire database based setup from a single command you
can use `db_control.sh`:

```bash
./scripts/db_control.sh start   # start all processes
./scripts/db_control.sh stop    # stop them again
```

This demonstrates communication between the main process and each component.

Each component stays active in its own loop waiting for commands from the
controller. The main loop polls the components continuously and occasionally
changes motor positions to verify everything is still connected.

The database process now shows a live table of the latest telemetry from every
component. Columns list the component, telemetry key, value and how many
seconds ago it was updated.
