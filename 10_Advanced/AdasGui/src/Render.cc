#include <algorithm>
#include <array>

#include "imgui.h"
#include "implot.h"

#include "DataLoader.hpp"
#include "DataLoaderConstants.hpp"
#include "Render.hpp"
#include "RenderConstants.hpp"

void render_cycle(std::size_t cycle, const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles)
{
    ImGui::SetNextWindowPos(ImVec2(0.0F, 0.0F));
    ImGui::SetNextWindowSize(ImVec2(WINDOWS_WIDTH, LANE_PLOT_TOTAL_HEIGHT));
    if (ImGui::Begin("MainWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        ImPlot::CreateContext();
        plot_lanes(ego_vehicle, vehicles);
        plot_table(ego_vehicle, vehicles);
        plot_cycle_number(cycle);
        ImGui::End();
    }
}

void plot_lanes(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles)
{
    if (ImPlot::BeginPlot("##Lane1", PLOT_DIM, PLOT_FLAGS))
    {
        ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_Lock, ImPlotAxisFlags_Lock | ImPlotAxisFlags_Invert);
        ImPlot::SetupAxisLimits(ImAxis_X1, -MAX_VIEW_RANGE_M, MAX_VIEW_RANGE_M, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1, LEFT_LEFT_BORDER, LEFT_RIGHT_BORDER, ImGuiCond_Always);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, VEHICLE_SCATTER_SIZE, ImVec4(0.5F, 0.5F, 0.5F, 1.0F));
        ImPlot::PlotScatter("FrontLeft", &vehicles.vehicles_left_lane[0].distance_m, &LEFT_LANE_OFFSET_M, 1);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, VEHICLE_SCATTER_SIZE, ImVec4(1.0F, 0.5F, 0.5F, 1.0F));
        ImPlot::PlotScatter("RearLeft", &vehicles.vehicles_left_lane[1].distance_m, &LEFT_LANE_OFFSET_M, 1);

        if (ego_vehicle.lane == LaneAssociationType::LEFT)
        {
            ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, VEHICLE_SCATTER_SIZE, ImVec4(0.7F, 0.5F, 0.5F, 1.0F));
            ImPlot::PlotScatter("Ego", &ego_vehicle.distance_m, &LEFT_LANE_OFFSET_M, 1);
        }

        ImPlot::EndPlot();
    }

    if (ImPlot::BeginPlot("##Lane2", PLOT_DIM, PLOT_FLAGS))
    {
        ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_Lock, ImPlotAxisFlags_Lock | ImPlotAxisFlags_Invert);
        ImPlot::SetupAxisLimits(ImAxis_X1, -MAX_VIEW_RANGE_M, MAX_VIEW_RANGE_M, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1, CENTER_LEFT_BORDER, CENTER_RIGHT_BORDER, ImGuiCond_Always);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, VEHICLE_SCATTER_SIZE, ImVec4(0.5F, 0.5F, 1.0F, 1.0F));
        ImPlot::PlotScatter("FrontCenter", &vehicles.vehicles_center_lane[0].distance_m, &CENTER_LANE_OFFSET_M, 1);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, VEHICLE_SCATTER_SIZE, ImVec4(0.75F, 0.5F, 1.0F, 1.0F));
        ImPlot::PlotScatter("RearCenter", &vehicles.vehicles_center_lane[1].distance_m, &CENTER_LANE_OFFSET_M, 1);

        if (ego_vehicle.lane == LaneAssociationType::CENTER)
        {
            ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, VEHICLE_SCATTER_SIZE, ImVec4(0.7F, 0.5F, 0.5F, 1.0F));
            ImPlot::PlotScatter("Ego", &ego_vehicle.distance_m, &CENTER_LANE_OFFSET_M, 1);
        }

        ImPlot::EndPlot();
    }

    if (ImPlot::BeginPlot("##Lane3", PLOT_DIM, PLOT_FLAGS))
    {
        ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_Lock, ImPlotAxisFlags_Lock | ImPlotAxisFlags_Invert);
        ImPlot::SetupAxisLimits(ImAxis_X1, -MAX_VIEW_RANGE_M, MAX_VIEW_RANGE_M, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1, RIGHT_LEFT_BORDER, RIGHT_RIGHT_BORDER, ImGuiCond_Always);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, VEHICLE_SCATTER_SIZE, ImVec4(0.75F, 0.5F, 0.75F, 1.0F));
        ImPlot::PlotScatter("FrontRight", &vehicles.vehicles_right_lane[0].distance_m, &RIGHT_LANE_OFFSET_M, 1);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, VEHICLE_SCATTER_SIZE, ImVec4(0.75F, 0.75F, 1.0F, 1.0F));
        ImPlot::PlotScatter("RearRight", &vehicles.vehicles_right_lane[1].distance_m, &RIGHT_LANE_OFFSET_M, 1);

        if (ego_vehicle.lane == LaneAssociationType::RIGHT)
        {
            ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, VEHICLE_SCATTER_SIZE, ImVec4(0.7F, 0.5F, 0.5F, 1.0F));
            ImPlot::PlotScatter("Ego", &ego_vehicle.distance_m, &RIGHT_LANE_OFFSET_M, 1);
        }

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

void plot_cycle_number(const std::size_t cycle)
{
    ImGui::SetNextWindowPos(ImVec2(0.0F, BELOW_LANES + CYCLE_OFFSET));
    ImGui::SetNextWindowSize(ImVec2(CYCLE_NUMBER_WIDTH, CYCLE_NUMBER_HEIGHT));
    if (ImGui::Begin("CycleWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        ImGui::Text("Cycle: %d", static_cast<std::int32_t>(cycle));
        ImGui::End();
    }
}
