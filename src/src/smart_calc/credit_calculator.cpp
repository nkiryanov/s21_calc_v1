#include "smart_calc/credit_calculator.hpp"

#include "imgui.h"

extern "C" {
#include "credit_calc/credit_calc.h"
}

namespace SmartCalc {

bool CreditCalculator::VerifyAndCalculateCreditData() {
  bool is_valid = get_credit_payments(&credit, &monthly_payments_data);

  is_credit_data_valid = is_valid;
  return is_valid;
}

void CreditCalculator::Draw() {
  ImGui::SetNextWindowPos(ImVec2(330, 10), ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(ImVec2(550, 360), ImGuiCond_FirstUseEver);

  ImGui::Begin("Credit Calculator", is_credit_open);
  CreditCalculator::DrawAndProceedCalculateButton();
  CreditCalculator::DrawInputData();

  ImGui::SeparatorText("Calculated Results:");
  if (is_credit_data_valid) CreditCalculator::DrawCalculatedResult();

  ImGui::End();
}

void CreditCalculator::DrawInputData() {
  ImGui::SeparatorText("Input Data");
  ImGui::Text("Credit amount:");
  ImGui::SameLine();
  ImGui::SetNextItemWidth(150);
  ImGui::InputDouble("##$$$", &credit.credit_amount);
  ImGui::Text("Term:");
  ImGui::SameLine();
  ImGui::Dummy(ImVec2(55, 0));
  ImGui::SameLine();
  ImGui::SetNextItemWidth(150);
  ImGui::InputInt("##term", (int *)(&credit.term));
  ImGui::SameLine();
  ImGui::SameLine();
  ImGui::RadioButton("years", (int *)(&credit.term_type), TERM_YEARS);
  ImGui::SameLine();
  ImGui::RadioButton("month", (int *)(&credit.term_type), TERM_MONTH);
  ImGui::Text("Interest rate:");
  ImGui::SetNextItemWidth(150);
  ImGui::SameLine();
  ImGui::InputDouble("##interest rate", &credit.interest_rate);
  ImGui::Text("Payment type:");
  ImGui::SameLine();
  ImGui::Dummy(ImVec2(5, 0));
  ImGui::SameLine();
  ImGui::RadioButton("differentiated", (int *)(&credit.credit_type),
                     DIFFERENTIATED);
  ImGui::SameLine();
  ImGui::RadioButton("annually", (int *)(&credit.credit_type), ANNUITY);
}

void CreditCalculator::DrawAndProceedCalculateButton() {
  if (ImGui::Button("Credit me !!!", ImVec2(150, 35))) {
    CreditCalculator::VerifyAndCalculateCreditData();
  }

  if (is_credit_data_valid == false) {
    ImVec4 red_color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    ImGui::SameLine();
    ImGui::TextColored(red_color, "The credit data is not valid");
  }
}

void CreditCalculator::DrawCalculatedResult() {
  ImGui::Text("Total Payment = %lf", monthly_payments_data.total_payed);
  ImGui::Text("Overpay = %lf", monthly_payments_data.overpayment);
  ImGui::SeparatorText("Monthly payments:");

  if (ImGui::BeginTable("split", 5)) {
    ImGui::TableNextColumn();
    ImGui::Text("Month");
    ImGui::TableNextColumn();
    ImGui::Text("This month");
    ImGui::TableNextColumn();
    ImGui::Text("Main part");
    ImGui::TableNextColumn();
    ImGui::Text("Credit part");
    ImGui::TableNextColumn();
    ImGui::Text("Left to pay");

    for (int i = 0; i != monthly_payments_data.month_count; ++i) {
      credit_monthly_payment_t data = monthly_payments_data.monthly_payments[i];

      ImGui::TableNextColumn();
      ImGui::Text("%d", i + 1);
      ImGui::TableNextColumn();
      ImGui::Text("%lf", data.payment);
      ImGui::TableNextColumn();
      ImGui::Text("%lf", data.main_part_payment);
      ImGui::TableNextColumn();
      ImGui::Text("%lf", data.tax_part_payment);
      ImGui::TableNextColumn();
      ImGui::Text("%lf", data.remaining_credit);
    }
    ImGui::EndTable();
  }
}

}  // namespace SmartCalc
