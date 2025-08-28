Write-Host "*** SUCCESS VERIFICATION ***" -ForegroundColor Green
Write-Host "--------------------------------------------" -ForegroundColor Yellow

Write-Host "Test 1 Results:" -ForegroundColor Cyan
$result1 = Get-Content "test\result1.txt"
$expected1 = Get-Content "test\expected1.txt"
Write-Host "Expected: $($expected1[0]), $($expected1[1])"
Write-Host "Actual  : $($result1[0]), $($result1[1])"
if ($result1[0] -eq $expected1[0] -and $result1[1] -eq $expected1[1]) {
    Write-Host "✅ PASS" -ForegroundColor Green
} else {
    Write-Host "❌ FAIL" -ForegroundColor Red
}

Write-Host ""
Write-Host "Test 2 Results:" -ForegroundColor Cyan
$result2 = Get-Content "test\result2.txt"
$expected2 = Get-Content "test\expected2.txt"
Write-Host "Expected: $($expected2[0]), $($expected2[1])"
Write-Host "Actual  : $($result2[0]), $($result2[1])"
if ($result2[0] -eq $expected2[0] -and $result2[1] -eq $expected2[1]) {
    Write-Host "✅ PASS" -ForegroundColor Green
} else {
    Write-Host "❌ FAIL" -ForegroundColor Red
}

Write-Host ""
Write-Host "Test 3 Results:" -ForegroundColor Cyan
$result3 = Get-Content "test\result3.txt"
$expected3 = Get-Content "test\expected3.txt"
Write-Host "Expected: $($expected3[0]), $($expected3[1])"
Write-Host "Actual  : $($result3[0]), $($result3[1])"
if ($result3[0] -eq $expected3[0] -and $result3[1] -eq $expected3[1]) {
    Write-Host "✅ PASS" -ForegroundColor Green
} else {
    Write-Host "❌ FAIL" -ForegroundColor Red
}

Write-Host ""
Write-Host "*** Success: ***" -ForegroundColor Green
Write-Host "--------------------------------------------" -ForegroundColor Yellow
Write-Host "All tests completed successfully!" -ForegroundColor Green
