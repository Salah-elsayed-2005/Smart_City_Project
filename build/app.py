import dash
import dash_bootstrap_components as dbc
from dash import dcc, html
from dash.dependencies import Input, Output, State
from dash.exceptions import PreventUpdate
import plotly.graph_objects as go
import smart_city  # Import compiled C++ module via pybind11

current_step = 0
total_steps = 0
steps = []


# Fetch node coordinates and graph data
city_coordinates = smart_city.get_city_coordinates()

road_network = smart_city.get_road_network()

# Prepare node and edge data for visualization
nodes = [
    {
        "id": i,
        "x": coord[0],
        "y": coord[1],
        "label": f"Node {i}"
    }
    for i, coord in enumerate(city_coordinates)
]

def get_edges():
    edges = []
    for i, row in enumerate(road_network):
        for j, weight in enumerate(row):
            if weight > 0:
                edges.append({"source": i, "target": j, "weight": weight})
    return edges

edges = get_edges()

def plot_graph():
    fig = go.Figure()

    # Add edges to the plot with capacities
    for edge in edges:
        x0, y0 = city_coordinates[edge["source"]]
        x1, y1 = city_coordinates[edge["target"]]
        fig.add_trace(go.Scatter(
            x=[x0, x1], y=[y0, y1],
            mode="lines+text",
            line=dict(color="black", width=2),
            text=["", f"{edge['weight']}", ""],
            textposition="middle center",
            hoverinfo="none"
        ))

    # Add nodes to the plot
    for node in nodes:
        fig.add_trace(go.Scatter(
            x=[node["x"]], y=[node["y"]],
            mode="markers+text",
            marker=dict(size=15, color="skyblue", line=dict(color="black", width=2)),
            text=node["label"],
            textposition="top center",
            hoverinfo="text"
        ))

    # Update layout for better visualization
    fig.update_layout(
        title="City Map Visualization",
        showlegend=False,
        xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
        yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
        margin=dict(l=10, r=10, t=50, b=10),
        plot_bgcolor="white"
    )
    return fig

app = dash.Dash(__name__, external_stylesheets=[dbc.themes.BOOTSTRAP])
app.title = "Smart City Visualization"

app.layout = dbc.Container(
    [
        # Title Row
        dbc.Row(
            dbc.Col(
                html.H1(
                    "Smart City Algorithm Visualization",
                    className="text-center text-primary my-4"
                ),
                width=12
            )
        ),

        # Main Content Row
        dbc.Row(
            [
                # Left Sidebar for Algorithm Parameters and Events
                dbc.Col(
                    [
                        # Algorithm Parameters Section
                        html.Div(
                            [
                                html.H5("Algorithm Parameters", className="text-secondary mb-3"),
                                html.Label("Select Source Node:"),
                                dcc.Input(
                                    id="source-input", type="number",
                                    min=0, max=len(road_network)-1, step=1, value=0,
                                    className="form-control mb-2"
                                ),
                                html.Label("Select Sink Node:"),
                                dcc.Input(
                                    id="sink-input", type="number",
                                    min=0, max=len(road_network)-1, step=1, value=5,
                                    className="form-control mb-3"
                                ),
                                dbc.Button(
                                    "Run Algorithm",
                                    id="run-button",
                                    color="primary",
                                    className="mt-3 w-100"
                                ),
                                dbc.Button(
                                    "Run Ford-Fulkerson",
                                    id="ford-fulkerson-button",
                                    color="success",
                                    className="mt-3 w-100"
                                ),
                                html.Hr(),
                            ],
                            className="mb-4"
                        ),

                        # Events Section
                        html.Div(
                            [
                                html.H5("Events", className="text-secondary mb-3"),
                                dbc.Button(
                                    "Trigger Earthquake",
                                    id="earthquake-button",
                                    color="danger",
                                    className="mb-2 w-100"
                                ),
                                dcc.Input(
                                    id="earthquake-node",
                                    type="number",
                                    placeholder="Damaged Node",
                                    className="form-control mb-2",
                                    min=0, max=len(road_network)-1, step=1
                                ),
                                dbc.Button(
                                    "Trigger Maintenance",
                                    id="maintenance-button",
                                    color="warning",
                                    className="mb-2 w-100"
                                ),
                                dcc.Input(
                                    id="maintenance-node",
                                    type="number",
                                    placeholder="Damaged Node",
                                    className="form-control mb-2",
                                    min=0, max=len(road_network)-1, step=1
                                ),
                                dbc.Button(
                                    "Trigger Traffic Congestion",
                                    id="traffic-button",
                                    color="info",
                                    className="mb-2 w-100"
                                ),
                                dcc.Input(
                                    id="traffic-node",
                                    type="number",
                                    placeholder="Congested Node",
                                    className="form-control mb-2",
                                    min=0, max=len(road_network)-1, step=1
                                ),
                            ],
                            className="mb-4"
                        ),html.Div(
                        [
                            dbc.Button("Previous Step", id="prev-step-button", color="secondary", className="me-2"),
                            dbc.Button("Next Step", id="next-step-button", color="primary"),
                        ],
                        className="d-flex justify-content-center my-3"
                    ),

                    ],
                    width=3,
                    className="bg-light p-4 rounded shadow-sm"
                ),

                # Right Content Area for Dropdown and Map
                dbc.Col(
                    [
                        # Dropdown for Network Type Selection
                        html.Div(
                            [
                                html.Label("Select Network Type:"),
                                dcc.Dropdown(
                                    id="network-dropdown",
                                    options=[
                                        {"label": "Road Network", "value": "road"},
                                        {"label": "Power Network", "value": "power"},
                                        {"label": "Datacenters Network", "value": "dc"}
                                    ],
                                    value="road",  # Default value
                                    className="mb-3"
                                ),
                            ],
                            className="mb-4"
                        ),

                        # Graph Visualization
                        dcc.Graph(
                            id="city-map",
                            figure=plot_graph(),
                            style={"height": "80vh"},
                            className="shadow-sm"
                        )
                    ],
                    width=9
                )
            ]
        ),

        # Metrics Row
        dbc.Row(
            dbc.Col(
                html.Div(
                    id="metrics",
                    className="text-center mt-3 text-info",
                    style={"fontSize": "18px"}
                ),
                width=12
            ),
            className="mt-3"
        )


    ],
    fluid=True
)


@app.callback(
    [Output("city-map", "figure", allow_duplicate=True), Output("metrics", "children", allow_duplicate=True)],
    [Input("run-button", "n_clicks")],
    [State("source-input", "value"), State("sink-input", "value")],
    prevent_initial_call=True
)
def run_shortest_path(n_clicks, source, sink):
    if n_clicks is None or source is None or sink is None or source == sink:
        raise PreventUpdate

    # Call the shortest path function
    route = smart_city.start_shortest_path(source, sink)

    # Prepare the updated graph
    fig = plot_graph()
    for i in range(len(route) - 1):
        x0, y0 = city_coordinates[route[i]]
        x1, y1 = city_coordinates[route[i + 1]]
        fig.add_trace(go.Scatter(
            x=[x0, x1], y=[y0, y1],
            mode="lines",
            line=dict(color="red", width=4),
            hoverinfo="none"
        ))

    return fig, f"Shortest path from {source} to {sink}: {route}"


@app.callback(
    [Output("city-map", "figure", allow_duplicate=True), Output("metrics", "children", allow_duplicate=True)],
    [Input("ford-fulkerson-button", "n_clicks")],
    [State("source-input", "value"), State("sink-input", "value")],
    prevent_initial_call=True
)
def run_ford_fulkerson(n_clicks, source, sink):
    if n_clicks is None or source is None or sink is None or source == sink:
        raise PreventUpdate

    # Run Ford-Fulkerson
    result = smart_city.start_ford_fulkerson(road_network, source, sink)
    max_flow = result.get_max_flow()  # Access max_flow using the method
    flow_network = result.get_flow()  # Access the flow matrix using the method
    capacity_network = result.get_cap()  # Access the capacity matrix using the method

    # Create a fresh graph
    fig = go.Figure()

    # Highlight only the paths used with flow > 0
    for i in range(len(flow_network)):
        for j in range(len(flow_network[i])):
            if flow_network[i][j] > 0:  # Only highlight paths with non-zero flow
                x0, y0 = city_coordinates[i]
                x1, y1 = city_coordinates[j]
                flow = flow_network[i][j]
                capacity = capacity_network[i][j]

                # Draw the edge
                fig.add_trace(go.Scatter(
                    x=[x0, x1], y=[y0, y1],
                    mode="lines",
                    line=dict(color="blue", width=4),  # Highlighted line
                    hoverinfo="none"
                ))

                # Add flow/capacity label at the midpoint of the edge
                midpoint_x = (x0 + x1) / 2
                midpoint_y = (y0 + y1) / 2
                fig.add_trace(go.Scatter(
                    x=[midpoint_x], y=[midpoint_y],
                    mode="text",
                    text=[f"{flow}/{capacity}"],  # Display flow/capacity
                    textposition="middle center",
                    hoverinfo="none"
                ))

    # Add nodes to ensure they are always visible
    for node in nodes:
        fig.add_trace(go.Scatter(
            x=[node["x"]], y=[node["y"]],
            mode="markers+text",
            marker=dict(size=15, color="skyblue", line=dict(color="black", width=2)),
            text=node["label"],
            textposition="top center",
            hoverinfo="text"
        ))

    fig.update_layout(
        title=f"Ford-Fulkerson Visualization (Max Flow: {max_flow})",
        showlegend=False,
        xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
        yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
        margin=dict(l=10, r=10, t=50, b=10),
        plot_bgcolor="white"
    )

    return fig, f"Max Flow from {source} to {sink}: {max_flow}"

@app.callback(
    [Output("city-map", "figure"), Output("metrics", "children")],
    [Input("network-dropdown", "value"),
     Input("prev-step-button", "n_clicks"),
     Input("next-step-button", "n_clicks")],
    prevent_initial_call=True
)
def update_visualization(selected_network, prev_clicks, next_clicks):
    global current_step, total_steps, steps

    # Handle new network selection
    ctx = dash.callback_context
    if ctx.triggered and ctx.triggered[0]["prop_id"] == "network-dropdown.value":
        current_step = 0  # Reset step counter

        if selected_network == "road":
            # Visualize Road Network
            return plot_graph(), "Visualizing the Road Network."

        elif selected_network in ["power", "dc"]:
            # Initialize MST steps for the selected network
            steps = (
                smart_city.start_MST_build_power_network()
                if selected_network == "power"
                else smart_city.start_MST_build_DC_network()
            )
            total_steps = len(steps)

            # Visualize the first step
            fig = go.Figure()
            for i in range(len(steps[0])):
                for j in range(len(steps[0][i])):
                    if steps[0][i][j] > 0:
                        x0, y0 = city_coordinates[i]
                        x1, y1 = city_coordinates[j]
                        fig.add_trace(go.Scatter(
                            x=[x0, x1], y=[y0, y1],
                            mode="lines",
                            line=dict(color="green" if selected_network == "power" else "purple", width=2),
                            hoverinfo="none"
                        ))

            # Add nodes
            for node in nodes:
                fig.add_trace(go.Scatter(
                    x=[node["x"]], y=[node["y"]],
                    mode="markers+text",
                    marker=dict(size=15, color="skyblue", line=dict(color="black", width=2)),
                    text=node["label"],
                    textposition="top center",
                    hoverinfo="text"
                ))

            fig.update_layout(
                title=f"{selected_network.capitalize()} Network - MST Step 1/{total_steps}",
                showlegend=False,
                xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                margin=dict(l=10, r=10, t=50, b=10),
                plot_bgcolor="white"
            )
            return fig, "Visualizing Step 1."

    # Handle Previous/Next Step Button Clicks
    triggered_id = ctx.triggered[0]["prop_id"].split(".")[0] if ctx.triggered else None

    if triggered_id == "prev-step-button":
        # Go to the previous step
        current_step = max(0, current_step - 1)

    elif triggered_id == "next-step-button":
        # Go to the next step
        current_step = min(total_steps - 1, current_step + 1)

    # Visualize the current step
    fig = go.Figure()
    for i in range(len(steps[current_step])):
        for j in range(len(steps[current_step][i])):
            if steps[current_step][i][j] > 0:
                x0, y0 = city_coordinates[i]
                x1, y1 = city_coordinates[j]
                fig.add_trace(go.Scatter(
                    x=[x0, x1], y=[y0, y1],
                    mode="lines",
                    line=dict(color="green" if selected_network == "power" else "purple", width=2),
                    hoverinfo="none"
                ))

    # Add nodes
    for node in nodes:
        fig.add_trace(go.Scatter(
            x=[node["x"]], y=[node["y"]],
            mode="markers+text",
            marker=dict(size=15, color="skyblue", line=dict(color="black", width=2)),
            text=node["label"],
            textposition="top center",
            hoverinfo="text"
        ))

    fig.update_layout(
        title=f"{selected_network.capitalize()} Network - MST Step {current_step + 1}/{total_steps}",
        showlegend=False,
        xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
        yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
        margin=dict(l=10, r=10, t=50, b=10),
        plot_bgcolor="white"
    )

    return fig, f"Visualizing Step {current_step + 1}/{total_steps}."

@app.callback(
    [Output("city-map", "figure", allow_duplicate=True), Output("metrics", "children", allow_duplicate=True)],
    [Input("earthquake-button", "n_clicks")],
    [State("earthquake-node", "value"), State("network-dropdown", "value")],
    prevent_initial_call=True
)

def handle_earthquake(n_clicks, damaged_node, selected_network):
    if n_clicks is None or damaged_node is None:
        raise PreventUpdate

    # Initialize Earthquake Event
    earthquake = smart_city.Earthquake(damaged_node)
    earthquake.trigger()

    fig = go.Figure()
    steps = []  # To store steps for visualization
    metrics = []  # To store metrics for display

    if selected_network == "road":
        # Road Network: Visualize Trigger Steps
        steps = earthquake.get_road_network_trigger_steps()
        for step_idx, step in enumerate(steps):
            for i in range(len(step)):
                for j in range(len(step[i])):
                    if step[i][j] > 0:
                        x0, y0 = city_coordinates[i]
                        x1, y1 = city_coordinates[j]
                        fig.add_trace(go.Scatter(
                            x=[x0, x1], y=[y0, y1],
                            mode="lines",
                            line=dict(color="orange", width=2),
                            hoverinfo="none"
                        ))

            fig.update_layout(
                title=f"Road Network - Trigger Step {step_idx + 1}/{len(steps)}",
                showlegend=False,
                xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                margin=dict(l=10, r=10, t=50, b=10),
                plot_bgcolor="white"
            )

        # Get Emergency Routes
        routes = earthquake.get_emergency_routes()
        for route_idx, route in enumerate(routes):
            for i in range(len(route) - 1):
                x0, y0 = city_coordinates[route[i]]
                x1, y1 = city_coordinates[route[i + 1]]
                fig.add_trace(go.Scatter(
                    x=[x0, x1], y=[y0, y1],
                    mode="lines+markers",
                    line=dict(color="red", width=4),
                    name=f"Emergency Route {route_idx + 1}"
                ))

            metrics.append(f"Emergency Route {route_idx + 1}: {route}")

    elif selected_network == "power":
        # Power Network: Trigger Steps
        steps = earthquake.get_power_network_trigger_steps()
        for step_idx, step in enumerate(steps):
            for i in range(len(step)):
                for j in range(len(step[i])):
                    if step[i][j] > 0:
                        x0, y0 = city_coordinates[i]
                        x1, y1 = city_coordinates[j]
                        fig.add_trace(go.Scatter(
                            x=[x0, x1], y=[y0, y1],
                            mode="lines",
                            line=dict(color="green", width=2),
                            hoverinfo="none"
                        ))

        # Handle Steps
        handle_steps = earthquake.get_power_network_handle_steps()
        for step_idx, step in enumerate(handle_steps):
            for i in range(len(step)):
                for j in range(len(step[i])):
                    if step[i][j] > 0:
                        x0, y0 = city_coordinates[i]
                        x1, y1 = city_coordinates[j]
                        fig.add_trace(go.Scatter(
                            x=[x0, x1], y=[y0, y1],
                            mode="lines",
                            line=dict(color="blue", width=2),
                            hoverinfo="none"
                        ))

    elif selected_network == "dc":
        # DC Network: Trigger Steps
        steps = earthquake.get_DC_network_trigger_steps()
        for step_idx, step in enumerate(steps):
            for i in range(len(step)):
                for j in range(len(step[i])):
                    if step[i][j] > 0:
                        x0, y0 = city_coordinates[i]
                        x1, y1 = city_coordinates[j]
                        fig.add_trace(go.Scatter(
                            x=[x0, x1], y=[y0, y1],
                            mode="lines",
                            line=dict(color="purple", width=2),
                            hoverinfo="none"
                        ))

        # Handle Steps
        handle_steps = earthquake.get_DC_network_handle_steps()
        for step_idx, step in enumerate(handle_steps):
            for i in range(len(step)):
                for j in range(len(step[i])):
                    if step[i][j] > 0:
                        x0, y0 = city_coordinates[i]
                        x1, y1 = city_coordinates[j]
                        fig.add_trace(go.Scatter(
                            x=[x0, x1], y=[y0, y1],
                            mode="lines",
                            line=dict(color="blue", width=2),
                            hoverinfo="none"
                        ))

    return fig, " | ".join(metrics) if metrics else f"Earthquake Triggered on {selected_network.capitalize()} Network."



if __name__ == "__main__":
    app.run_server(debug=True)
