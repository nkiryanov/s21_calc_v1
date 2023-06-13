#include "smart_calc/deposit_calculator.hpp"

#include "imgui.h"

extern "C" {
#include "deposit_calc/deposit_calc.h"
}

namespace SmartCalc {

bool DepositCalculator::VerifyAndCalculateDepositData() {
  bool is_valid = get_deposit_payments(&deposit, &earned);

  is_deposit_data_valid = is_valid;
  return is_valid;
}

void DepositCalculator::Draw() {
  ImGui::SetNextWindowPos(ImVec2(330, 380), ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(ImVec2(550, 320), ImGuiCond_FirstUseEver);

  ImGui::Begin("Deposit Calculator", is_deposit_open);
  DepositCalculator::DrawAndProceedCalculateButton();
  DepositCalculator::DrawInputData();

  ImGui::SeparatorText("Calculated Results:");
  if (is_deposit_data_valid) DepositCalculator::DrawCalculatedResult();

  ImGui::End();
}

void DepositCalculator::DrawInputData() {
  ImGui::SeparatorText("Input Data");
  ImGui::Text("Initial amount:");
  ImGui::SameLine();
  ImGui::SetNextItemWidth(150);
  ImGui::InputDouble("##$$$", &deposit.initial_amount);

  ImGui::Text("Term:");
  ImGui::SameLine();
  ImGui::Dummy(ImVec2(62, 0));
  ImGui::SameLine();
  ImGui::SetNextItemWidth(150);
  ImGui::InputInt("##term", (int *)(&deposit.term));

  ImGui::Text("Interest Rate:");
  ImGui::SameLine();
  ImGui::Spacing();
  ImGui::SameLine();
  ImGui::SetNextItemWidth(150);
  ImGui::InputDouble("##interest rate", &deposit.interest_rate);
  ImGui::SameLine();
  ImGui::Text("Tax Rate:");
  ImGui::SetNextItemWidth(150);
  ImGui::SameLine();
  ImGui::InputDouble("##tax rate", &deposit.tax_rate);

  ImGui::Text("Capitalization:");
  ImGui::SameLine();
  ImGui::Checkbox("##capitalization applied", &deposit.is_capitalized);
  ImGui::SameLine();
  ImGui::RadioButton("years", (int *)(&deposit.payment_frequency),
                     DEPOSIT_FREQUENCY_YEARS);
  ImGui::SameLine();
  ImGui::RadioButton("month", (int *)(&deposit.payment_frequency),
                     DEPOSIT_FREQUENCY_MONTH);

  ImGui::Text("Replenishment:");
  ImGui::SameLine();
  ImGui::Spacing();
  ImGui::SetNextItemWidth(150);
  ImGui::SameLine();
  ImGui::InputDouble("(monthly)##replenishment", &deposit.how_much_replenished);

  ImGui::Text("Withdraw:");
  ImGui::SameLine();
  ImGui::Dummy(ImVec2(35, 0));
  ImGui::SetNextItemWidth(150);
  ImGui::SameLine();
  ImGui::InputDouble("(monthly)##replenishment", &deposit.how_much_withdraw);
}

void DepositCalculator::DrawAndProceedCalculateButton() {
  if (ImGui::Button("Deposit me !!!", ImVec2(150, 35))) {
    DepositCalculator::VerifyAndCalculateDepositData();
  }

  if (is_deposit_data_valid == false) {
    ImVec4 red_color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    ImGui::SameLine();
    ImGui::TextColored(red_color, "The deposit data is not valid");
  }
}

void DepositCalculator::DrawCalculatedResult() {
  ImGui::Text("Total in Bank = %lf", earned.final_amount);
  ImGui::Text("Total Earned = %lf", earned.earned_amount);
  ImGui::Text("Total Taxed = %lf", earned.tax_amount);
}

}  // namespace SmartCalc
