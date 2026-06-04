#!/usr/bin/env python3
import argparse
from pathlib import Path

import plotly.graph_objects as go
from plotly.subplots import make_subplots


def is_point_line(line: str) -> bool:
    parts = line.split()
    if len(parts) != 3:
        return False

    try:
        [float(value) for value in parts]
    except ValueError:
        return False

    return True


def parse_point(line: str) -> tuple[float, float, float]:
    x, y, z = line.split()
    return float(x), float(y), float(z)


def read_sectioned_points(filename: Path) -> dict[str, list[tuple[float, float, float]]]:
    sections: dict[str, list[tuple[float, float, float]]] = {}
    current_section = "points"

    with filename.open("r", encoding="utf-8") as file:
        for raw_line in file:
            line = raw_line.strip()

            if not line:
                continue

            if not is_point_line(line):
                current_section = line.lower()
                sections.setdefault(current_section, [])
                continue

            sections.setdefault(current_section, []).append(parse_point(line))

    return sections


def points_to_xyz(points: list[tuple[float, float, float]]):
    return (
        [point[0] for point in points],
        [point[1] for point in points],
        [point[2] for point in points],
    )


def add_points_trace(
    fig,
    points: list[tuple[float, float, float]],
    *,
    row: int,
    col: int,
    name: str,
    size: int = 4,
    mode: str = "markers",
):
    if not points:
        return

    x, y, z = points_to_xyz(points)

    fig.add_trace(
        go.Scatter3d(
            x=x,
            y=y,
            z=z,
            mode=mode,
            name=name,
            marker={"size": size},
            line={"width": 4},
        ),
        row=row,
        col=col,
    )


def add_shape_traces(fig, sections, row: int, col: int):
    add_points_trace(
        fig,
        sections.get("bottom_base", []),
        row=row,
        col=col,
        name="Нижнее основание",
        size=4,
    )
    add_points_trace(
        fig,
        sections.get("top_base", []),
        row=row,
        col=col,
        name="Верхнее основание",
        size=4,
    )
    add_points_trace(
        fig,
        sections.get("base", []),
        row=row,
        col=col,
        name="Основание",
        size=4,
    )
    add_points_trace(
        fig,
        sections.get("apex", []),
        row=row,
        col=col,
        name="Вершина",
        size=8,
    )
    add_points_trace(
        fig,
        sections.get("axis", []),
        row=row,
        col=col,
        name="Ось",
        size=7,
        mode="markers+lines",
    )
    add_points_trace(
        fig,
        sections.get("generatrix", []),
        row=row,
        col=col,
        name="Образующая",
        size=4,
        mode="markers+lines",
    )


def add_plane_traces(fig, sections, row: int, col: int):
    add_points_trace(
        fig,
        sections.get("points", []),
        row=row,
        col=col,
        name="Точки плоскости",
        size=3,
    )
    add_points_trace(
        fig,
        sections.get("origin", []),
        row=row,
        col=col,
        name="Origin плоскости",
        size=8,
    )


def add_intersection_traces(fig, sections, row: int, col: int):
    points = sections.get("points", [])

    if not points:
        points = sections.get("intersection", [])

    add_points_trace(
        fig,
        points,
        row=row,
        col=col,
        name="Кривая пересечения",
        size=5,
        mode="markers",
    )


def collect_all_points(*section_maps) -> list[tuple[float, float, float]]:
    result = []

    for sections in section_maps:
        for points in sections.values():
            result.extend(points)

    return result


def make_equal_scene_ranges(fig, all_points):
    if not all_points:
        return

    xs, ys, zs = points_to_xyz(all_points)

    min_x, max_x = min(xs), max(xs)
    min_y, max_y = min(ys), max(ys)
    min_z, max_z = min(zs), max(zs)

    center_x = (min_x + max_x) / 2.0
    center_y = (min_y + max_y) / 2.0
    center_z = (min_z + max_z) / 2.0

    max_range = max(max_x - min_x, max_y - min_y, max_z - min_z)

    if max_range == 0.0:
        max_range = 1.0

    half = max_range / 2.0

    scene_update = {
        "xaxis": {"title": "X", "range": [center_x - half, center_x + half]},
        "yaxis": {"title": "Y", "range": [center_y - half, center_y + half]},
        "zaxis": {"title": "Z", "range": [center_z - half, center_z + half]},
        "aspectmode": "cube",
    }

    fig.update_scenes(**scene_update)


def build_debug_figure(shape_sections, plane_sections, intersection_sections):
    fig = make_subplots(
        rows=2,
        cols=2,
        specs=[
            [{"type": "scene"}, {"type": "scene"}],
            [{"type": "scene"}, {"type": "scene"}],
        ],
        subplot_titles=[
            "Shape",
            "Plane",
            "Intersection curve",
            "All together",
        ],
    )

    add_shape_traces(fig, shape_sections, row=1, col=1)
    add_plane_traces(fig, plane_sections, row=1, col=2)
    add_intersection_traces(fig, intersection_sections, row=2, col=1)

    add_shape_traces(fig, shape_sections, row=2, col=2)
    add_plane_traces(fig, plane_sections, row=2, col=2)
    add_intersection_traces(fig, intersection_sections, row=2, col=2)

    all_points = collect_all_points(shape_sections, plane_sections, intersection_sections)
    make_equal_scene_ranges(fig, all_points)

    fig.update_layout(
        title="Geometry debug view",
        height=950,
        width=1200,
        showlegend=True,
        margin={"l": 0, "r": 0, "t": 70, "b": 0},
    )

    return fig


def main():
    parser = argparse.ArgumentParser(
        description="Interactive 3D debug viewer for sampled shape, plane and intersection points."
    )
    parser.add_argument("--shape", required=True, help="Path to shape points txt")
    parser.add_argument("--plane", required=True, help="Path to plane points txt")
    parser.add_argument("--intersection", required=True, help="Path to intersection points txt")
    parser.add_argument(
        "--output",
        default=None,
        help="Output html path. Default: debug_scene.html near shape file",
    )

    args = parser.parse_args()

    shape_file = Path(args.shape)
    plane_file = Path(args.plane)
    intersection_file = Path(args.intersection)

    output_file = Path(args.output) if args.output else shape_file.with_name("debug_scene.html")

    shape_sections = read_sectioned_points(shape_file)
    plane_sections = read_sectioned_points(plane_file)
    intersection_sections = read_sectioned_points(intersection_file)

    fig = build_debug_figure(shape_sections, plane_sections, intersection_sections)
    fig.write_html(output_file)

    print(f"Saved interactive debug scene to: {output_file}")


if __name__ == "__main__":
    main()
