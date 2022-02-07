#include <algorithm>
#include <array>
#include <vector>

#include "imgui.h"
#include "implot.h"

#include "DataLoader.hpp"
#include "DataLoaderConstants.hpp"
#include "Render.hpp"
#include "RenderConstants.hpp"

void render_cycle(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles)
{
    ImGui::SetNextWindowPos(ImVec2(0.0F, 0.0F));
    ImGui::SetNextWindowSize(ImVec2(WINDOWS_WIDTH, LANE_PLOT_TOTAL_HEIGHT));
    if (ImGui::Begin("MainWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        ImPlot::CreateContext();
        plot_lanes(ego_vehicle, vehicles);
        plot_table(ego_vehicle, vehicles);
        ImGui::End();
    }
}

void plot_solid_line(const float border, std::string_view label)
{
    const float xs_left_left[2] = {-VIEW_RANGE_M, VIEW_RANGE_M};
    const float ys_left_left[2] = {border, border};
    ImPlot::SetNextLineStyle(LINE_COLOR, 3.0F);
    ImPlot::PlotLine(label.data(), xs_left_left, ys_left_left, 2);
}

void plot_dashed_lines(const float border, std::string_view label)
{
    const auto slice_length = (2.0F * VIEW_RANGE_M) / 40.0F;
    const auto empty_length = 2.0F;
    const auto dashed_length = slice_length - empty_length;
    const auto num_slices = static_cast<std::uint32_t>((2.0F * VIEW_RANGE_M) / slice_length);

    for (uint32_t it = 0; it < num_slices; it++)
    {
        float it_f32 = static_cast<float>(it);

        const float xs_center_left[2] = {-VIEW_RANGE_M + it_f32 * slice_length,
                                         -VIEW_RANGE_M + it_f32 * slice_length + dashed_length};
        const float ys_center_left[2] = {border, border};
        ImPlot::SetNextLineStyle(LINE_COLOR, 3.0F);
        ImPlot::PlotLine(label.data(), xs_center_left, ys_center_left, 2);
    }
}

void plot_ego_vehicle(const VehicleType &ego_vehicle, std::string_view label)
{
    const auto ego_marker = ImPlotMarker_Square;
    const auto ego_color = ImVec4(0.7F, 0.5F, 0.5F, 1.0F);

    switch (ego_vehicle.lane)
    {
    case LaneAssociationType::LEFT:
    {
        ImPlot::SetNextMarkerStyle(ego_marker, VEHICLE_SCATTER_SIZE, ego_color);
        ImPlot::PlotScatter(label.data(), &ego_vehicle.distance_m, &LEFT_LANE_OFFSET_M, 1);
        break;
    }
    case LaneAssociationType::CENTER:
    {
        ImPlot::SetNextMarkerStyle(ego_marker, VEHICLE_SCATTER_SIZE, ego_color);
        ImPlot::PlotScatter(label.data(), &ego_vehicle.distance_m, &CENTER_LANE_OFFSET_M, 1);

        break;
    }
    case LaneAssociationType::RIGHT:
    {
        ImPlot::SetNextMarkerStyle(ego_marker, VEHICLE_SCATTER_SIZE, ego_color);
        ImPlot::PlotScatter(label.data(), &ego_vehicle.distance_m, &RIGHT_LANE_OFFSET_M, 1);

        break;
    }
    case LaneAssociationType::NONE:
    default:
    {
        break;
    }
    }
}

void plot_lane_vehicles(const std::array<VehicleType, 2> &vehicles,
                        const float offset_m,
                        std::string_view label_front,
                        std::string_view label_rear)
{
    ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, VEHICLE_SCATTER_SIZE);
    const auto xs_front = vehicles[0].distance_m;
    const auto ys_front = offset_m;
    ImPlot::PlotScatter(label_front.data(), &xs_front, &ys_front, 1);

    ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, VEHICLE_SCATTER_SIZE);
    const auto xs_rear = vehicles[1].distance_m;
    const auto ys_rear = offset_m;
    ImPlot::PlotScatter(label_rear.data(), &xs_rear, &ys_rear, 1);
}

void plot_lanes(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles)
{
    if (ImPlot::BeginPlot("##Lanes", PLOT_DIM, PLOT_FLAGS))
    {
        ImPlot::SetupAxes("Rel. LongDist. (m)", "Rel. LatDist. (m)", ImPlotAxisFlags_Lock, AXES_FLAGS);
        ImPlot::SetupAxisLimits(ImAxis_X1, -VIEW_RANGE_M, VIEW_RANGE_M, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1,
                                LEFT_LEFT_BORDER - 0.05F,
                                RIGHT_RIGHT_BORDER + 0.05F,
                                ImGuiCond_Always);

        plot_solid_line(LEFT_LEFT_BORDER, "LeftLeftLane");
        plot_dashed_lines(CENTER_LEFT_BORDER, "CenterLeftLane");
        plot_dashed_lines(CENTER_RIGHT_BORDER, "CenterRightLane");
        plot_solid_line(RIGHT_RIGHT_BORDER, "RightRightLane");

        plot_lane_vehicles(vehicles.vehicles_left_lane, LEFT_LANE_OFFSET_M, "LeftFront", "LeftRear");
        plot_lane_vehicles(vehicles.vehicles_center_lane, CENTER_LANE_OFFSET_M, "CenterFront", "CenterRear");
        plot_lane_vehicles(vehicles.vehicles_right_lane, RIGHT_LANE_OFFSET_M, "RightFront", "RightRear");

        plot_ego_vehicle(ego_vehicle, "Ego");

        ImPlot::EndPlot();
    }
}

void plot_vehicle_in_table(const VehicleType &vehicle, std::string_view position_name)
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("%s", position_name.data());
    ImGui::TableNextColumn();
    ImGui::Text("%d", vehicle.id);
    ImGui::TableNextColumn();
    ImGui::Text("%d", static_cast<std::int32_t>(vehicle.lane));
    ImGui::TableNextColumn();
    ImGui::Text("%f", vehicle.distance_m);
    ImGui::TableNextColumn();
    ImGui::Text("%f", vehicle.speed_mps);
}

void plot_table(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles)
{
    ImGui::SetNextWindowPos(ImVec2(0.0F, BELOW_LANES));
    ImGui::SetNextWindowSize(ImVec2(VEHICLE_TABLE_WIDTH, VEHICLE_TABLE_HEIGHT));
    if (ImGui::Begin("TableWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        if (ImGui::BeginTable("Table", 5, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuter))
        {
            ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
            ImGui::TableNextColumn();
            ImGui::Text("Pos:");
            ImGui::TableNextColumn();
            ImGui::Text("ID:");
            ImGui::TableNextColumn();
            ImGui::Text("Lane:");
            ImGui::TableNextColumn();
            ImGui::Text("Distance:");
            ImGui::TableNextColumn();
            ImGui::Text("Speed:");

            plot_vehicle_in_table(ego_vehicle, "Ego");
            plot_vehicle_in_table(vehicles.vehicles_left_lane[0], "FrontLeft");
            plot_vehicle_in_table(vehicles.vehicles_left_lane[1], "RearLeft");
            plot_vehicle_in_table(vehicles.vehicles_center_lane[0], "FrontCenter");
            plot_vehicle_in_table(vehicles.vehicles_center_lane[1], "RearCenter");
            plot_vehicle_in_table(vehicles.vehicles_right_lane[0], "FrontRight");
            plot_vehicle_in_table(vehicles.vehicles_right_lane[1], "RearRight");

            ImGui::EndTable();
        }

        ImGui::End();
    }
}
