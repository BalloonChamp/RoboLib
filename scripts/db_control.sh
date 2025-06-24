#!/bin/bash
# Control all database-based components.
# Usage: db_control.sh start|stop

set -e
PID_DIR="/tmp/robolib_pids"
DB_SCRIPTS=(run_database.sh run_dbmotor1.sh run_dbmotor2.sh run_dbsensor.sh run_scheduler.sh)

start() {
    mkdir -p "$PID_DIR"
    for script in "${DB_SCRIPTS[@]}"; do
        ./scripts/$script &
        echo $! > "$PID_DIR/$script.pid"
    done
    echo "Started components."
}

stop() {
    if [ -d "$PID_DIR" ]; then
        for pidfile in "$PID_DIR"/*.pid; do
            [ -f "$pidfile" ] && kill "$(cat "$pidfile")" 2>/dev/null && rm "$pidfile"
        done
    fi
    echo "Stopped components."
}

case "$1" in
    start) start;;
    stop) stop;;
    *) echo "Usage: $0 {start|stop}"; exit 1;;
 esac
