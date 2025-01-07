import dash
import dash_bootstrap_components as dbc
from dash import dcc, html
from dash.dependencies import Input, Output, State
from dash.exceptions import PreventUpdate
import plotly.graph_objects as go
import smart_city  # Import compiled C++ module via pybind11

current_step = 0
trigger_steps = []
handle_steps = []



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

                                dcc.Dropdown(
                                    id="maintenance-dropdown",
                                    options=[],  # Options are dynamically populated
                                    placeholder="Select a node",
                                    className="mb-3"

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
                                    min=0, max=69, step=1
                                ),dcc.Location(id="url", refresh=True),
                            ],
                            className="mb-4"
                        ),html.Div(
                        [
                            dbc.Button("Reset", id="reset-button", color="danger", className="me-2"),
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
        ),html.Div(
        [
            dbc.Button("Start Animation", id="start-animation", color="primary", className="mb-3"),
            dcc.Interval(
                id="animation-interval",
                interval=1000,  # 1 second per step
                n_intervals=0,
                disabled=True  # Initially disabled
            )
        ]
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
    global all_traffic_edges  # Include congested edges

    if n_clicks is None or source is None or sink is None or source == sink:
        raise PreventUpdate

    # Call the shortest path function
    route = smart_city.start_shortest_path(source, sink)

    # Prepare the updated graph
    fig = go.Figure()

    # Add all edges as light gray
    for i, row in enumerate(road_network):
        for j, weight in enumerate(row):
            if weight > 0:
                x0, y0 = city_coordinates[i]
                x1, y1 = city_coordinates[j]
                fig.add_trace(go.Scatter(
                    x=[x0, x1], y=[y0, y1],
                    mode="lines",
                    line=dict(color="gray", width=1),  # Light gray edges
                    hoverinfo="none"
                ))

    # Add congested edges in red
    if 'all_traffic_edges' in globals():
        for edge in all_traffic_edges:
            x0, y0 = city_coordinates[edge[0]]
            x1, y1 = city_coordinates[edge[1]]
            fig.add_trace(go.Scatter(
                x=[x0, x1], y=[y0, y1],
                mode="lines",
                line=dict(color="red", width=2),  # Congested edges in red
                hoverinfo="none"
            ))

    # Add shortest path edges in blue
    for i in range(len(route) - 1):
        x0, y0 = city_coordinates[route[i]]
        x1, y1 = city_coordinates[route[i + 1]]
        fig.add_trace(go.Scatter(
            x=[x0, x1], y=[y0, y1],
            mode="lines",
            line=dict(color="blue", width=4),  # Shortest path edges in blue
            hoverinfo="none"
        ))

    # Add all nodes
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
        title="Shortest Path with Traffic Congestion",
        showlegend=False,
        xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
        yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
        margin=dict(l=10, r=10, t=50, b=10),
        plot_bgcolor="white"
    )

    return fig, f"Shortest path from Node {source} to Node {sink} calculated."



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
    [
        Output("city-map", "figure", allow_duplicate=True),
        Output("metrics", "children", allow_duplicate=True),
        Output("animation-interval", "disabled", allow_duplicate=True)
    ],
    [
        Input("earthquake-button", "n_clicks"),
        Input("start-animation", "n_clicks"),
        Input("animation-interval", "n_intervals")
    ],
    [
        State("earthquake-node", "value"),
        State("network-dropdown", "value")
    ],
    prevent_initial_call=True
)
def handle_earthquake_and_animation(
        earthquake_clicks, animation_clicks, n_intervals, damaged_node, selected_network
):
    global current_step, trigger_steps, handle_steps, emergency_routes

    ctx = dash.callback_context
    triggered_id = ctx.triggered[0]["prop_id"].split(".")[0] if ctx.triggered else None

    # Trigger Earthquake Event
    if triggered_id == "earthquake-button":
        if damaged_node is None:
            return plot_graph(), "Select a valid node.", True

        earthquake = smart_city.Earthquake(damaged_node)
        earthquake.trigger()
        earthquake.handle()

        # Retrieve steps and emergency routes based on the selected network
        trigger_steps, handle_steps, emergency_routes = [], [], []

        if selected_network == "road":
            trigger_steps = earthquake.get_road_network_trigger_steps()
            emergency_routes = earthquake.get_emergency_routes()
        elif selected_network == "power":
            trigger_steps = earthquake.get_power_network_trigger_steps()
            handle_steps = earthquake.get_power_network_handle_steps()
        elif selected_network == "dc":
            trigger_steps = earthquake.get_DC_network_trigger_steps()
            handle_steps = earthquake.get_DC_network_handle_steps()
        else:
            return plot_graph(), "Earthquake is only applicable to Road, Power, or Datacenters Networks.", True

        current_step = 0  # Reset step counter
        return plot_graph(), f"Earthquake triggered on {selected_network.capitalize()} Network. Start animation to visualize steps.", True

    # Start Animation
    elif triggered_id == "start-animation":
        if not trigger_steps and not handle_steps:
            return plot_graph(), "No steps to animate. Trigger earthquake first.", True

        return dash.no_update, "Animation started.", False  # Enable interval

    # Animation Logic: Display Each Step
    elif triggered_id == "animation-interval":
        total_steps = len(trigger_steps) + len(handle_steps)

        if current_step >= total_steps:
            # Show the final state and emergency routes after the animation completes
            fig = go.Figure()

            # Add emergency routes (Road Network only)
            if selected_network == "road" and emergency_routes:
                for idx, route in enumerate(emergency_routes):
                    if not route:
                        continue  # Skip empty routes
                    for i in range(len(route) - 1):
                        x0, y0 = city_coordinates[route[i]]
                        x1, y1 = city_coordinates[route[i + 1]]
                        fig.add_trace(go.Scatter(
                            x=[x0, x1], y=[y0, y1],
                            mode="lines+markers",
                            line=dict(color="green", width=6),
                            name=f"Emergency Route {idx + 1}"
                        ))

            # Add the final adjacency matrix
            final_matrix = handle_steps[-1] if handle_steps else trigger_steps[-1]
            for i in range(len(final_matrix)):
                for j in range(len(final_matrix[i])):
                    if final_matrix[i][j] > 0:
                        x0, y0 = city_coordinates[i]
                        x1, y1 = city_coordinates[j]
                        fig.add_trace(go.Scatter(
                            x=[x0, x1], y=[y0, y1],
                            mode="lines",
                            line=dict(color="blue", width=2),
                            hoverinfo="none"
                        ))

            # Add all nodes
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
                title="Final Earthquake State",
                showlegend=False,
                xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                margin=dict(l=10, r=10, t=50, b=10),
                plot_bgcolor="white"
            )

            return fig, "Animation complete. Final state displayed.", True  # Disable interval

        # Show current step in the animation
        fig = go.Figure()

        # Determine if the current step is in the trigger or handle phase
        if current_step < len(trigger_steps):
            step = trigger_steps[current_step]
            step_color = "orange"  # Trigger steps
            step_label = f"Trigger Step {current_step + 1}"
        else:
            step = handle_steps[current_step - len(trigger_steps)]
            step_color = "blue"  # Handle (MST) steps
            step_label = f"Handle Step {current_step - len(trigger_steps) + 1}"

        # Visualize the current adjacency matrix
        for i in range(len(step)):
            for j in range(len(step[i])):
                if step[i][j] > 0:
                    x0, y0 = city_coordinates[i]
                    x1, y1 = city_coordinates[j]
                    fig.add_trace(go.Scatter(
                        x=[x0, x1], y=[y0, y1],
                        mode="lines",
                        line=dict(color=step_color, width=2),
                        hoverinfo="none"
                    ))

        # Add all nodes
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
            title=f"{step_label} of {selected_network.capitalize()}",
            showlegend=False,
            xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
            yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
            margin=dict(l=10, r=10, t=50, b=10),
            plot_bgcolor="white"
        )

        current_step += 1  # Move to the next step
        return fig, f"Visualizing {step_label}.", False

    return dash.no_update, dash.no_update, dash.no_update



@app.callback(
    [
        Output("city-map", "figure", allow_duplicate=True),
        Output("metrics", "children", allow_duplicate=True),
        Output("animation-interval", "disabled")
    ],
    [
        Input("maintenance-button", "n_clicks"),
        Input("start-animation", "n_clicks"),
        Input("animation-interval", "n_intervals")
    ],
    [
        State("maintenance-dropdown", "value"),
        State("network-dropdown", "value")
    ],
    prevent_initial_call=True
)
def handle_maintenance_and_animation(
        maintenance_clicks, animation_clicks, n_intervals, damaged_node, selected_network
):
    global current_step, trigger_steps, handle_steps

    ctx = dash.callback_context
    triggered_id = ctx.triggered[0]["prop_id"].split(".")[0] if ctx.triggered else None

    # Initialize Maintenance when button is clicked
    if triggered_id == "maintenance-button":
        if damaged_node is None or selected_network not in ["power", "dc"]:
            return plot_graph(), "Select a valid node and network.", True

        maintenance = smart_city.Maintenance(damaged_node)
        maintenance.trigger()
        maintenance.handle()

        if selected_network == "power":
            trigger_steps = maintenance.get_power_network_trigger_steps()
            handle_steps = maintenance.get_power_network_handle_steps()
        elif selected_network == "dc":
            trigger_steps = maintenance.get_DC_network_trigger_steps()
            handle_steps = maintenance.get_DC_network_handle_steps()

        current_step = 0  # Reset to the first step
        return plot_graph(), "Maintenance triggered. Start animation to visualize steps.", True

    # Start Animation when button is clicked
    elif triggered_id == "start-animation":
        if not trigger_steps and not handle_steps:
            return plot_graph(), "No steps to animate. Trigger maintenance first.", True

        return dash.no_update, "Animation started.", False  # Enable interval

    # Animation Logic: Update Visualization for Each Step
    elif triggered_id == "animation-interval":
        total_steps = len(trigger_steps) + len(handle_steps)

        if current_step >= total_steps:
            # Show the latest updates after animation completes
            fig = go.Figure()

            # Display the final adjacency matrix
            final_matrix = handle_steps[-1] if handle_steps else trigger_steps[-1]
            for i in range(len(final_matrix)):
                for j in range(len(final_matrix[i])):
                    if final_matrix[i][j] > 0:
                        x0, y0 = city_coordinates[i]
                        x1, y1 = city_coordinates[j]
                        fig.add_trace(go.Scatter(
                            x=[x0, x1], y=[y0, y1],
                            mode="lines",
                            line=dict(color="blue", width=2),
                            hoverinfo="none"
                        ))

            # Add all nodes to ensure they remain visible
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
                title="Final Maintenance State",
                showlegend=False,
                xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                margin=dict(l=10, r=10, t=50, b=10),
                plot_bgcolor="white"
            )

            return fig, "Animation complete. Final state displayed.", True  # Disable interval

        fig = go.Figure()

        # Determine if we are in the trigger or handle phase
        if current_step < len(trigger_steps):
            step = trigger_steps[current_step]
            step_color = "orange"  # Trigger steps in orange
        else:
            step = handle_steps[current_step - len(trigger_steps)]
            step_color = "blue"  # Handle (MST) steps in blue

        # Visualize the current step
        for i in range(len(step)):
            for j in range(len(step[i])):
                if step[i][j] > 0:
                    x0, y0 = city_coordinates[i]
                    x1, y1 = city_coordinates[j]
                    fig.add_trace(go.Scatter(
                        x=[x0, x1], y=[y0, y1],
                        mode="lines",
                        line=dict(color=step_color, width=2),
                        hoverinfo="none"
                    ))

        # Add all nodes to ensure they remain visible
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
            title=f"Step {current_step + 1} of {total_steps}",
            showlegend=False,
            xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
            yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
            margin=dict(l=10, r=10, t=50, b=10),
            plot_bgcolor="white"
        )

        current_step += 1  # Move to the next step
        return fig, f"Visualizing Step {current_step} of {total_steps}.", False

    return dash.no_update, dash.no_update, dash.no_update




@app.callback(
    [Output("city-map", "figure", allow_duplicate=True), Output("metrics", "children", allow_duplicate=True)],
    [Input("traffic-button", "n_clicks")],
    [State("traffic-node", "value"), State("network-dropdown", "value")],
    prevent_initial_call=True
)
def handle_traffic_congestion(n_clicks, congested_node, selected_network):
    global all_traffic_edges  # Store all congested edges globally

    if n_clicks is None or congested_node is None:
        raise PreventUpdate

    # Redirect if the special value is entered
    if congested_node == 69:
        import webbrowser
        webbrowser.open("https://www.youtube.com/watch?v=ujr8N-vFaYg")
        return dash.no_update, dash.no_update

    # Ensure Traffic Congestion is only triggered on the Road Network
    if selected_network != "road":
        return plot_graph(), "Traffic Congestion can only be triggered on the Road Network."

    # Initialize Traffic Congestion Event
    traffic = smart_city.TrafficCongestion(congested_node)
    traffic.trigger()  # Trigger traffic congestion

    if 'all_traffic_edges' not in globals():
        all_traffic_edges = []  # Initialize if not already defined

    # Add new congested edges to the global list
    new_traffic_edges = []  # Store edges for this node
    for i in range(len(road_network)):
        if road_network[congested_node][i] > 0:
            new_traffic_edges.append((congested_node, i))

    all_traffic_edges.extend(new_traffic_edges)  # Append new edges

    # Remove duplicates to avoid redundant visualization
    all_traffic_edges = list(set(all_traffic_edges))

    fig = go.Figure()

    # Plot all edges as light gray for the base graph
    for i, row in enumerate(road_network):
        for j, weight in enumerate(row):
            if weight > 0:
                x0, y0 = city_coordinates[i]
                x1, y1 = city_coordinates[j]
                fig.add_trace(go.Scatter(
                    x=[x0, x1], y=[y0, y1],
                    mode="lines",
                    line=dict(color="gray", width=1),  # Light gray edges
                    hoverinfo="none"
                ))

    # Highlight all congested edges in red
    for edge in all_traffic_edges:
        x0, y0 = city_coordinates[edge[0]]
        x1, y1 = city_coordinates[edge[1]]
        fig.add_trace(go.Scatter(
            x=[x0, x1], y=[y0, y1],
            mode="lines",
            line=dict(color="red", width=2),  # Highlight all congested edges
            hoverinfo="none"
        ))

    # Add all nodes to the graph to ensure they remain visible
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
        title="Traffic Congestion Visualization - Road Network",
        showlegend=False,
        xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
        yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
        margin=dict(l=10, r=10, t=50, b=10),
        plot_bgcolor="white"
    )

    return fig, f"Traffic Congestion Triggered at Node {congested_node}."



@app.callback(
    [Output("city-map", "figure", allow_duplicate=True), Output("metrics", "children", allow_duplicate=True)],
    [Input("reset-button", "n_clicks")],
    prevent_initial_call=True
)
def reset_graph(n_clicks):
    global current_step, total_steps, steps, all_traffic_edges

    smart_city.boom_boom()

    if n_clicks is None:
        raise PreventUpdate

    # Reset global variables
    current_step = 0
    total_steps = 0
    steps = []
    all_traffic_edges = []

    # Create the original graph with light gray edges
    fig = go.Figure()

    # Plot all edges in light gray
    for i, row in enumerate(road_network):
        for j, weight in enumerate(row):
            if weight > 0:
                x0, y0 = city_coordinates[i]
                x1, y1 = city_coordinates[j]
                fig.add_trace(go.Scatter(
                    x=[x0, x1], y=[y0, y1],
                    mode="lines",
                    line=dict(color="gray", width=1),  # Light gray edges
                    hoverinfo="none"
                ))

    # Add all nodes to the graph
    for node in nodes:
        fig.add_trace(go.Scatter(
            x=[node["x"]], y=[node["y"]],
            mode="markers+text",
            marker=dict(size=15, color="skyblue", line=dict(color="black", width=2)),
            text=node["label"],
            textposition="top center",
            hoverinfo="text"
        ))

    # Update layout
    fig.update_layout(
        title="Original Graph - Reset",
        showlegend=False,
        xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
        yaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
        margin=dict(l=10, r=10, t=50, b=10),
        plot_bgcolor="white"
    )

    return fig, "Graph reset to the original state."

@app.callback(
    Output("maintenance-dropdown", "options"),
    [Input("network-dropdown", "value")],
    prevent_initial_call=True
)
def update_maintenance_dropdown(selected_network):
    if selected_network == "power":
        return [{"label": f"Node {i}", "value": i} for i in range(8, 11)]
    elif selected_network == "dc":
        return [{"label": f"Node {i}", "value": i} for i in range(11, 14)]
    return []


if __name__ == "__main__":
    app.run_server(debug=True)