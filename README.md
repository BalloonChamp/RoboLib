# RoboLib

Example framework for robot components communicating through a central
`Database` process. Components publish telemetry and receive commands
via the database rather than opening direct TCP connections to the main
controller.

## Build

```bash
./scripts/build.sh
```

## Run

### Database example

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

This demonstrates communication between a scheduler process and each
component. The scheduler periodically sends commands through the
database while components update their telemetry at fixed intervals.

The database process now shows a live table of the latest telemetry from every
component. Columns list the component, telemetry key, value and how many
seconds ago it was updated.
